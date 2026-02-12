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
	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|AI")
	float AcceptanceRadius{500.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|AI")
	float MinAttackDelay{.1f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|AI")
	float MaxAttackDelay{.5f};
	
	UFUNCTION(BlueprintImplementableEvent, Category="SAS|AI")
	float GetTimelineLength();
	
protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="SAS|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
