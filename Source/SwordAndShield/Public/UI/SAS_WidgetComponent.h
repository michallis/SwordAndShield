// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"

#include "SAS_WidgetComponent.generated.h"


class ASAS_BaseCharacter;
class USAS_AbilitySystemComponent;
class USAS_AttributeSet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SWORDANDSHIELD_API USAS_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;
	
private:
	TWeakObjectPtr<ASAS_BaseCharacter> SasCharacter;
	TWeakObjectPtr<USAS_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<USAS_AttributeSet> AttributeSet;
	
	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UFUNCTION()
	void BindToAttributeChanges();
};
