// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SAS_GameplayAbility.h"
#include "SAS_Primary.generated.h"

/**
 * 
 */
UCLASS()
class SWORDANDSHIELD_API USAS_Primary : public USAS_GameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="SAS|Abilities")
	void HitBoxOverlapTest();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	float HitBoxRadius = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	float HitBoxForwardOffset = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	float HitBoxElevationOffset = 20.0f;
};
