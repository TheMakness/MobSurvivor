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
	// Sets default values for this component's properties
	UKnockbackComponent();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FFloatCurve Curve;
	void Knockback(float Force, const FVector& Direction);

	UPROPERTY(EditAnywhere)
	float Duration;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void KnockbackLerp(float alpha) const;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner;

	float Lerp;
	float PlayRate;
	bool bIsStart;

	float Force;
	FVector Direction;
	FVector StartLerpLocation;
	FVector EndLerpLocation;

	
};
