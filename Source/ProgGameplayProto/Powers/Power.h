// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Power.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API APower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APower();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void Cooldown(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CountdownStartValue;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Countdown;
	UPROPERTY(BlueprintReadOnly)
	bool IsCountdownStart;
};
