// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIScore.h"
#include "GameFramework/Actor.h"
#include "HttpModule.h"

#include "UHttpRequestSubsystem.generated.h"

struct FAPIScore;
struct FAPIUser;


UENUM(BlueprintType)
enum class ERequestCompleteStatus : uint8
{
	Success,
	Failed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignInRequestCompleteDelegate, ERequestCompleteStatus, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPostScoreRequestCompleteDelegate, ERequestCompleteStatus, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSignOutRequestCompleteDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetScoreRequestCompleteDelegate, ERequestCompleteStatus, Status, const TArray<FAPIScore>&, Scores);

UCLASS()
class PROGGAMEPLAYPROTO_API UHttpRequestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	const FString API_URL = "http://localhost:3001";

	FHttpModule* Http;

	// Store the current request endpoint.
	FString RequestEndpoint;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess=true))
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

	UPROPERTY(BlueprintAssignable)
	FGetScoreRequestCompleteDelegate GetScoreRequestComplete;
	
public:
	
	// Sets default values for this actor's properties
	UHttpRequestSubsystem();

	UFUNCTION(BlueprintCallable)
	void SignIn(const FAPIUser User);

	void PostScore(const FAPIScore Score);

	UFUNCTION(BlueprintCallable)
	void GetScores();

	UFUNCTION(BlueprintCallable)
	void SignOut();

	UFUNCTION(BlueprintCallable)
	FAPIUser GetSignedInUser() const;

	bool IsLoggedIn() const;

private:
	void HandleRequestErrors(EHttpRequestStatus::Type ErrorStatus) const;
};
