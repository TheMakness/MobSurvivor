// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int, NewGoldValue);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGGAMEPLAYPROTO_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoldComponent();
	UFUNCTION(BlueprintCallable)
		FORCEINLINE int GetGoldAmount() { return GoldAmount; };
	UFUNCTION(BlueprintCallable)
		void AddGold(int GoldValue);
	UPROPERTY(BlueprintAssignable)
		FOnGoldChanged OnGoldChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
		int GoldAmount;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
