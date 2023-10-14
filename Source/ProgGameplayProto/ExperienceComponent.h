// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExperienceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperienceChanged, float, NewExperienceValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UExperienceComponent();

	UPROPERTY(BlueprintAssignable)
	FOnExperienceChanged OnExperienceChanged;

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp OnLevelUp;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveFloat* ExperienceCurve;

	float CurrentExperience = 0;
	float CurrentLevelExperienceTarget = 0;
	int32 CurrentLevel = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AddExperience(float Amount);

	virtual void LevelUp();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual float GetCurrentExperiencePercentage();
};
