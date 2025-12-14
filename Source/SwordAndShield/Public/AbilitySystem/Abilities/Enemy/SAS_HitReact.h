// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SAS_GameplayAbility.h"
#include "SAS_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class SWORDANDSHIELD_API USAS_HitReact : public USAS_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="SAS|HitReact")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category="SAS|HitReact")
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadOnly, Category="SAS|HitReact")
	FVector ToInstigator;
};
