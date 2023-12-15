// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpRequestManager.h"

#include "JsonObjectConverter.h"
#include "JsonScore.h"




AHttpRequestManager::AHttpRequestManager()
{

}

void AHttpRequestManager::SendScore()
{
	MakeRequest();

}

void AHttpRequestManager::MakeRequest()
{
    
	FHttpModule& httpModule = FHttpModule::Get();
	FHttpRequestPtr pRequest = httpModule.CreateRequest();

	pRequest->SetVerb(TEXT("POST"));
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	FJsonScore ScoreObj = FJsonScore("af04e6c68a6ab43de27a33803ae31fa00376a145d9858b57dfd18b26d20b7861",10);
	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(ScoreObj, JsonString,0,0);
	pRequest->SetContentAsString(JsonString);
	pRequest->SetURL("http://127.0.0.1:3000/score");

    pRequest->OnProcessRequestComplete().BindLambda(
        // Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
        // class's methods in the callback.
        [&](
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable {

                if (connectedSuccessfully) {

                    // We should have a JSON response - attempt to process it.
                    
                }
                else {
                    switch (pRequest->GetStatus()) {
                    case EHttpRequestStatus::Failed_ConnectionError:
                        UE_LOG(LogTemp, Error, TEXT("Connection failed."));
                    default:
                        UE_LOG(LogTemp, Error, TEXT("Request failed."));
                    }
                }
        });

	pRequest->ProcessRequest();

}


