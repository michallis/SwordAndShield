// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SAS_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SWORDANDSHIELD_API USAS_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SAS|Debug")
	bool bDrawDebugs = false;
};
