// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SAS_WaitGameplayEvent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SAS_BlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection: uint8
{
	Left,
	Right,
	Front,
	Back
};

/**
 * Return type for detecting players and their distance to the 
 * calling actor
 */
USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance{0.f};
};

UCLASS()
class SWORDANDSHIELD_API USAS_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="SAS|Utils")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure, Category="SAS|Utils")
	static FName GetHitDirectionName(const EHitDirection HitDirection);
	
	UFUNCTION(BlueprintCallable, Category="SAS|Utils")
	static FClosestActorWithTagResult FindClosesActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag);
	
	// DataTag is for the Set by Caller Magnitude (gameplay effect magnitude)
	UFUNCTION(BlueprintCallable, Category="SAS|Utils")
	static void SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, const FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage);
};



