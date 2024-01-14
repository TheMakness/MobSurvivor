// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int, NewGoldValue);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGoldComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetGoldAmount() const { return GoldAmount; };
	
	UFUNCTION(BlueprintCallable)
	void AddGold(int GoldValue);

	UPROPERTY(BlueprintAssignable)
	FOnGoldChanged OnGoldChanged;

private:
	int GoldAmount = 0;

	float BonusGoldMultiplier = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Save gold amount into game instance

	UFUNCTION()
	virtual void SaveGold();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IncrementGoldMultiplier(const float IncrementValue);
};
