// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpRequestManager.h"

#include "JsonObjectConverter.h"
#include "JsonScore.h"




TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequestManager::CreateRequest()
{

	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = httpModule.CreateRequest();

	pRequest->SetVerb(TEXT("POST"));
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	//FJsonScore ScoreObj = FJsonScore("af04e6c68a6ab43de27a33803ae31fa00376a145d9858b57dfd18b26d20b7861",10);

	FString JsonString;
	//FJsonObjectConverter::UStructToJsonObjectString(ScoreObj, JsonString);

	pRequest->SetContentAsString(JsonString);
	pRequest->SetURL("127.0.0.1:3000/score");

	return pRequest;
}

void HttpRequestManager::SendRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest)
{
	pRequest->ProcessRequest();
}

