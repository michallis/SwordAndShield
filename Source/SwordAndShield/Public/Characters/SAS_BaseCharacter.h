// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "SAS_BaseCharacter.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class SWORDANDSHIELD_API ASAS_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASAS_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; };
	
	UPROPERTY(BlueprintAssignable, Category="SAS|Events")
	FASCInitialized OnASCInitialized;
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes();

private:
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Effects")
	TSubclassOf<UGameplayEffect>InitializeAttributesEffect;
};
