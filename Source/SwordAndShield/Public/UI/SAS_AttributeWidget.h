// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystem/SAS_AttributeSet.h"

#include "SAS_AttributeWidget.generated.h"

/**
 * Attribute widget using both an attribute and its corresponding max attribute
 * Modelled as a Tuple<K,V> while both are attribute keys
 */
UCLASS()
class SWORDANDSHIELD_API USAS_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|Attributes")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|Attributes")
	FGameplayAttribute MaxAttribute;
	
	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, const USAS_AttributeSet* AttributeSet);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue);
};
