// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAS_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SWORDANDSHIELD_API USAS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(BlueprintCallable, Category="SAS|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level);
	
	UFUNCTION(BlueprintCallable, Category="SAS|Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);
	
	
private:
	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};
