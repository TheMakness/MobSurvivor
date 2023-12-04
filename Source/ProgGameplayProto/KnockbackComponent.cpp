// Fill out your copyright notice in the Description page of Project Settings.


#include "KnockbackComponent.h"


// Sets default values for this component's properties
UKnockbackComponent::UKnockbackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UKnockbackComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	PlayRate = 1 / Duration;
	// ...
	
}




// Called every frame
void UKnockbackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsStart) return;

	if(Lerp < 1)
	{
		Lerp += DeltaTime * PlayRate;
		KnockbackLerp(Lerp);
	}
	else
	{
		bIsStart = false;
		Lerp = 0;
		Owner->SetActorLocation(EndLerpLocation);
		Owner->SetActorEnableCollision(true);
	}

	

	// ...
}

void UKnockbackComponent::Knockback(const float force, const FVector& direction)
{
	if(bIsStart) return;

	Owner->SetActorEnableCollision(false);

	bIsStart = true;
	Force = force;
	Direction = direction;
	StartLerpLocation = Owner->GetActorLocation();
	EndLerpLocation = StartLerpLocation + (Direction * Force);

	DrawDebugSphere(GetWorld(), EndLerpLocation, 1, 16, FColor::Red, false, 5);
	DrawDebugSphere(GetWorld(), StartLerpLocation, 1, 16, FColor::Green, false, 5);
}

void UKnockbackComponent::KnockbackLerp(float alpha) const
{
	const FVector NewLocation = FMath::LerpStable(StartLerpLocation, EndLerpLocation, Lerp);
	Owner->SetActorLocation(NewLocation);
}


