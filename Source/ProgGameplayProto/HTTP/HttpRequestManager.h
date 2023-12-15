// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


class PROGGAMEPLAYPROTO_API HttpRequestManager
{
	
public:	
	// Sets default values for this actor's properties
	HttpRequestManager();

public:	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateRequest();
	
	void SendRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest);

};
