// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnockbackComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UKnockbackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FFloatCurve Curve;
	
	UPROPERTY(EditAnywhere)
	float Duration;

private:
	UPROPERTY()
	AActor* Owner;

	float Lerp;
	float PlayRate;
	bool bIsStart;

	float Force;
	FVector Direction;
	FVector StartLerpLocation;
	FVector EndLerpLocation;

public:
	UKnockbackComponent();

	void Knockback(float Force, const FVector& Direction);

protected:
	virtual void BeginPlay() override;

	void KnockbackLerp(float Alpha) const;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
