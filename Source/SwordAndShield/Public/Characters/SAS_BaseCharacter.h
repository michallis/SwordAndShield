// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "SAS_BaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UGameplayEffect;
class UAttributeSet;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);


/**
 * TST
 * 
 */
UCLASS(Abstract)
class SWORDANDSHIELD_API ASAS_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASAS_BaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; };
	bool IsAlive() const { return bAlive; }
	void SetAliveState(bool bAliveStatus) { bAlive = bAliveStatus; }
	
	UPROPERTY(BlueprintAssignable, Category="SAS|Events")
	FASCInitialized OnASCInitialized;
	
	UFUNCTION(BlueprintCallable, Category="SAS|Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable, Category="SAS|Attributes")
	void ResetAttributes();
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes();
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChange);
	virtual void HandleDeath();
	
	void ExecuteGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect);

private:
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Effects")
	TSubclassOf<UGameplayEffect>InitializeAttributesEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Effects")
	TSubclassOf<UGameplayEffect>ResetAttributesEffect;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Replicated)
	bool bAlive = true;
};
