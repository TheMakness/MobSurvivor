#pragma once

#include "CoreMinimal.h"
#include "APIUser.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FAPIUser
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Email;

	// Password is only set when signing up, otherwise it is empty
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Password;

	FAPIUser() : Email(""), Password("") {}

	FAPIUser(const FString& Email) : Email(Email), Password("") {}
	
	FAPIUser(const FString& Email, const FString& Password) : Email(Email), Password(Password) {}
};
