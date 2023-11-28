// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerComponent.generated.h"

class APlayerCharacter;
class UPowerPUData;
class APower;


UCLASS( Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROGGAMEPLAYPROTO_API UPowerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerComponent();

	void Initialise(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	const APlayerCharacter* GetPlayerOwner() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Call the Behaviour implementation of the power only if the cooldown is finished
	 */
	UFUNCTION(BlueprintCallable)
	void Use();

protected:
	/**
	 * Actual behaviour implementation of the power. Override this method to give behaviour to the Power
	 */
	UFUNCTION(BlueprintNativeEvent)
	void UseBehaviour();
	
	// Reference to the Power Data Asset class
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UPowerPUData> PowerData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Countdown;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHasCountdownStarted;

private:
	void Cooldown(float DeltaTime);

	UPROPERTY(VisibleAnywhere)
	float CountdownStartValue;

	TObjectPtr<APlayerCharacter> PlayerOwner;
};
