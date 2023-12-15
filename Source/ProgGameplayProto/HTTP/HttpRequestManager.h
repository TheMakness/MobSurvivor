// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpRequestManager.generated.h"

UCLASS(Blueprintable)
class PROGGAMEPLAYPROTO_API AHttpRequestManager : public AInfo
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AHttpRequestManager();

	UFUNCTION(BlueprintCallable)
		void SendScore();

	void MakeRequest();

};
