// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"

#include "UHttpRequestSubsystem.generated.h"

struct FAPIScore;
struct FAPIUser;

DECLARE_LOG_CATEGORY_EXTERN(LogHttp, Log, All);

UENUM(BlueprintType)
enum class ERequestCompleteStatus : uint8
{
	Success,
	Failed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignInRequestCompleteDelegate, ERequestCompleteStatus, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostScoreRequestCompleteDelegate, ERequestCompleteStatus, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSignOutRequestCompleteDelegate);

UCLASS()
class PROGGAMEPLAYPROTO_API UHttpRequestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	const FString API_URL = "http://localhost:3001";

	FHttpModule* Http;

	// Store the current request endpoint.
	FString RequestEndpoint;

	bool bSignedIn;
	
	TObjectPtr<FAPIUser> SignedInUser;

	// Store the user JWT token for future requests.
	FString JwtToken;

	UPROPERTY(BlueprintAssignable)
	FSignInRequestCompleteDelegate SignInRequestComplete;

	UPROPERTY(BlueprintAssignable)
	FPostScoreRequestCompleteDelegate PostScoreRequestComplete;

	UPROPERTY(BlueprintAssignable)
	FSignOutRequestCompleteDelegate SignOutRequestComplete;
	
public:
	
	// Sets default values for this actor's properties
	UHttpRequestSubsystem();

	UFUNCTION(BlueprintCallable)
	void SignIn(const FAPIUser User);

	void PostScore(const FAPIScore Score);

	UFUNCTION(BlueprintCallable)
	void SignOut();

	UFUNCTION(BlueprintCallable)
	FAPIUser GetSignedInUser() const;

private:
	void HandleRequestErrors(EHttpRequestStatus::Type ErrorStatus) const;
};
