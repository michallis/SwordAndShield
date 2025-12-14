// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "SAS_BaseCharacter.h"
#include "SAS_EnemyCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class SWORDANDSHIELD_API ASAS_EnemyCharacter : public ASAS_BaseCharacter
{
	GENERATED_BODY()

public:
	ASAS_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="SAS|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
