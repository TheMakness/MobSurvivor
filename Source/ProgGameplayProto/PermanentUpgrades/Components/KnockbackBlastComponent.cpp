// Fill out your copyright notice in the Description page of Project Settings.


#include "KnockbackBlastComponent.h"

#include "ProgGameplayProto/Health.h"
#include "ProgGameplayProto/KnockbackComponent.h"
#include "ProgGameplayProto/Enemies/Enemy.h"
#include "ProgGameplayProto/Player/PlayerCharacter.h"

#define COLLISION_WEAPON ECC_GameTraceChannel2

void UKnockbackBlastComponent::BeginPlay()
{
	Super::BeginPlay();
	Cast<APlayerCharacter>(GetOwner())->GetHealth()->OnHealthChangedWithoutParameters.AddDynamic(this, &UKnockbackBlastComponent::CheckCollision);
}

void UKnockbackBlastComponent::CheckCollision()
{
	AActor* Owner = GetOwner();
	TArray<FHitResult> outHits;
	const FCollisionShape shape = FCollisionShape::MakeSphere(ZoneSize);
	FCollisionQueryParams params;
	params.AddIgnoredActor(Owner);

	GetWorld()->SweepMultiByChannel(outHits, Owner->GetActorLocation(), Owner->GetActorLocation(), FQuat::Identity, COLLISION_WEAPON, shape, params);

	for (int i = 0; i < outHits.Num(); i++)
	{
		if (IsValid(LastActorHit))
			if (LastActorHit == outHits[i].GetActor()) continue;
		AActor* OtherActor = outHits[i].GetActor();
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (IsValid(Enemy))
		{
			UKnockbackComponent* KnockbackComponent = Enemy->GetComponentByClass<UKnockbackComponent>();
			if(KnockbackComponent)
			{
				FVector Dir = Enemy->GetActorLocation() - Owner->GetActorLocation();
				Dir.Z = 0;
				Dir.Normalize();
				KnockbackComponent->Knockback(Force,Dir);
			}
		}
		

	}
}





