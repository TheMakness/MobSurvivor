// Fill out your copyright notice in the Description page of Project Settings.


#include "UHttpRequestSubsystem.h"

#include "APIScore.h"
#include "JsonObjectConverter.h"
#include "APIUser.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY(LogHttp);

UHttpRequestSubsystem::UHttpRequestSubsystem() :
	Http(&FHttpModule::Get()),
	RequestEndpoint(""),
	bSignedIn(false),
	SignedInUser(nullptr)
{
	Http->AddDefaultHeader("Content-Type", "application/json");
}

void UHttpRequestSubsystem::SignIn(const FAPIUser User)
{
	FString RequestBody;
	FJsonObjectConverter::UStructToJsonObjectString(User, RequestBody, 0, 0);

	RequestEndpoint = API_URL + "/signing";

	const FHttpRequestPtr Request = Http->CreateRequest();
	Request->SetURL(RequestEndpoint);
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	Request->OnProcessRequestComplete().BindLambda(
		[&, User](const FHttpRequestPtr& Req, const FHttpResponsePtr& Res, const bool bConnectedSuccessfully) mutable
		{
			if (bConnectedSuccessfully)
			{
				TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
				const auto JsonReader = TJsonReaderFactory<>::Create(Res->GetContentAsString());

				if (FJsonSerializer::Deserialize(JsonReader, Json))
				{
					if (Req->GetResponse()->GetResponseCode() >= 200 && Req->GetResponse()->GetResponseCode() < 300)
					{
						JwtToken = Json->GetStringField("token");

						UE_LOG(LogHttp, Display, TEXT("[%s] Request succeeded. JWT: %s"), *RequestEndpoint, *JwtToken);

						bSignedIn = true;

						// We should probably get the user email from the response, but for now we'll just use the one we sent.
						SignedInUser = new FAPIUser(User.Email);

						SignInRequestComplete.Broadcast(ERequestCompleteStatus::Success);
						return;
					}
					else if (Req->GetResponse()->GetResponseCode() >= 400 && Req->GetResponse()->GetResponseCode() < 500)
					{
						UE_LOG(LogHttp, Error, TEXT("[%s] Bad request: %s"), *RequestEndpoint, *Json->GetStringField("message"));
					}
					else
					{
						UE_LOG(LogHttp, Error, TEXT("[%s] Request failed due to server error."), *RequestEndpoint);
					}
				}
				else
				{
					UE_LOG(LogHttp, Error, TEXT("[%s] Cannot parse JSON."), *RequestEndpoint);
				}
			}
			else
			{
				HandleRequestErrors(Req->GetStatus());
			}

			SignInRequestComplete.Broadcast(ERequestCompleteStatus::Failed);
		}
	);

	Request->ProcessRequest();
}

void UHttpRequestSubsystem::PostScore(const FAPIScore Score)
{
	FString RequestBody;
	FJsonObjectConverter::UStructToJsonObjectString(Score, RequestBody, 0, 0);

	RequestEndpoint = API_URL + "/score";

	const FHttpRequestPtr Request = Http->CreateRequest();
	Request->SetURL(RequestEndpoint);
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	Request->OnProcessRequestComplete().BindLambda(
		[&](const FHttpRequestPtr& Req, const FHttpResponsePtr& Res, const bool bConnectedSuccessfully) mutable
		{
			if (bConnectedSuccessfully)
			{
				TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
				const auto JsonReader = TJsonReaderFactory<>::Create(Res->GetContentAsString());

				if (FJsonSerializer::Deserialize(JsonReader, Json))
				{
					if (Req->GetResponse()->GetResponseCode() >= 200 && Req->GetResponse()->GetResponseCode() < 300)
					{
						UE_LOG(LogHttp, Display, TEXT("[%s] Request succeeded."), *RequestEndpoint);

						PostScoreRequestComplete.Broadcast(ERequestCompleteStatus::Success);
						return;
					}
					else if (Req->GetResponse()->GetResponseCode() >= 400 && Req->GetResponse()->GetResponseCode() < 500)
					{
						UE_LOG(LogHttp, Error, TEXT("[%s] Bad request: %s"), *RequestEndpoint, *Json->GetStringField("message"));
					}
					else
					{
						UE_LOG(LogHttp, Error, TEXT("[%s] Request failed due to server error."), *RequestEndpoint);
					}
				}
				else
				{
					UE_LOG(LogHttp, Error, TEXT("[%s] Cannot parse JSON."), *RequestEndpoint);
				}
			}
			else
			{
				HandleRequestErrors(Req->GetStatus());
			}

			PostScoreRequestComplete.Broadcast(ERequestCompleteStatus::Failed);
		}
	);

	Request->ProcessRequest();
}

void UHttpRequestSubsystem::SignOut()
{
	bSignedIn = false;
	JwtToken = "";
	SignedInUser = nullptr;

	SignOutRequestComplete.Broadcast();
}

FAPIUser UHttpRequestSubsystem::GetSignedInUser() const
{
	return SignedInUser ? *SignedInUser : FAPIUser("Guest");
}

void UHttpRequestSubsystem::HandleRequestErrors(const EHttpRequestStatus::Type ErrorStatus) const
{
	switch (ErrorStatus)
	{
	case EHttpRequestStatus::Failed_ConnectionError:
		UE_LOG(LogHttp, Error, TEXT("[%s] Connection failed."), *RequestEndpoint);
	default:
		UE_LOG(LogHttp, Error, TEXT("[%s] Request failed."), *RequestEndpoint);
	}
}
