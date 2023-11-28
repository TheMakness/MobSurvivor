// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../ExperienceComponent.h"
#include "../Health.h"
#include "../GameUtils.h"
#include "InputActionValue.h"
#include "../Bonuses/BonusData.h"
#include "Components/SphereComponent.h"
#include "../Drops/Drop.h"
#include "../Weapons/WeaponComponent.h"
#include "Logging/StructuredLog.h"
#include "../Weapons/WeaponData.h"
#include "../Weapons/WeaponProjectile.h"
#include "../Powers/Power.h"
#include "../Powers/PowerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/GoldComponent.h"
#include "ProgGameplayProto/MobSurvivorInstance.h"
#include "ProgGameplayProto/ProgGameplayProtoGameMode.h"
#include "ProgGameplayProto/StatsUpgradeComponent.h"
#include "ProgGameplayProto/PermanentUpgrades/PowerPUData.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProgGameplayProtoCharacter

APlayerCharacter* APlayerCharacter::Instance = nullptr;
APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");

	Health = CreateDefaultSubobject<UHealth>("Health");

	Experience = CreateDefaultSubobject<UExperienceComponent>("Experience");

	DropsCollector = CreateDefaultSubobject<USphereComponent>("Drops Collector");
	DropsCollector->SetupAttachment(GetCapsuleComponent());

	Gold = CreateDefaultSubobject<UGoldComponent>("Gold");

	StatsUpgrade = CreateDefaultSubobject<UStatsUpgradeComponent>("StatsComponent");
}

bool APlayerCharacter::WantsToShoot()
{
	return bIsHoldingShoot || bIsAutoFire;
}

void APlayerCharacter::SetupDefaultWeapon()
{
	Weapon->InitializeWeapon(this);

	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(IsValid(GI))
		Weapon->SetData(GI->GetEquippedWeapon());
	
	
	

	for (int32 i = 0; i < DefaultBonuses.Num(); i++)
	{
		DefaultBonuses[i]->Apply(this, Weapon);
	}
}

void APlayerCharacter::SetupDefaultPower()
{
	UMobSurvivorInstance* GI = Cast<UMobSurvivorInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GI))
		DefaultPowerData = GI->GetEquippedPower();

	Power = Cast<UPowerComponent>(AddComponentByClass(DefaultPowerData->GetComponent(), false, this->GetTransform(), false));
	Power->Initialise(this);
}

void APlayerCharacter::SetupDefaultStatsUpgrades()
{
	StatsUpgrade->ApplyUpgrades();
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	RegisterInstance();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Setup Weapon
	SetupDefaultWeapon();

	//Setup Power
	SetupDefaultPower();

	//Apply Stats Upgrades
	SetupDefaultStatsUpgrades();
	
	FActorSpawnParameters SpawnInfo;
//	PowerInstance = GetWorld()->SpawnActor<APower>(Power->CurrentPower,UGameUtils::GetMainCharacter()->GetActorLocation(), UGameUtils::GetMainCharacter()->GetActorRotation(),SpawnInfo);
//	PowerInstance->AttachToActor(UGameUtils::GetMainCharacter(), FAttachmentTransformRules::KeepRelativeTransform,NAME_Actor);
	DropsCollector->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnDropsCollectorBeginOverlap);

	Health->OnHealthDie.AddDynamic(this,&APlayerCharacter::Die);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::RegisterInstance()
{
	Instance = this;
}

void APlayerCharacter::OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADrop* drop = Cast<ADrop>(OtherActor);

	if (!IsValid(drop)) return;

	drop->StartCollection(this);
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::UsePower);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopShoot);
		EnhancedInputComponent->BindAction(AutoFireAction, ETriggerEvent::Started, this, &APlayerCharacter::AutoFire);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = true;
}

void APlayerCharacter::StopShoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = false;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::UsePower(const FInputActionValue& Value)
{
	if (IsValid(Power))
	{
		Power->Use();
	}
}


void APlayerCharacter::AutoFire(const FInputActionValue& Value)
{
	bIsAutoFire = !bIsAutoFire;
}

void APlayerCharacter::Die()
{
	Cast<AProgGameplayProtoGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
}
