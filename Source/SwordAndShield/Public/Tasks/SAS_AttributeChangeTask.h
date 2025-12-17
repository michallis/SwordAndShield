// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SAS_AttributeChangeTask.generated.h"

class UAbilitySystemComponent;
struct FOnAttributeChangeData;

/**
 * Example of defining a dynamic delegate
 * 1. Declare a delegate
 * 2. create FOnAttributechanged
 * 3. static constructor
 * 4. Create a listen function (Attribute Change for given attribute)
 * 5. Bind to call back to execute logic
 * 6. Create an EndTask method to unbind and clean up
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class SWORDANDSHIELD_API USAS_AttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;
	
	// Factory pattern creates the node in Blueprints
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true),Category="SAS|Tasks")
	static USAS_AttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);
	
	UFUNCTION(BlueprintCallable, Category="SAS|Tasks")
	void EndTask();
	
	TWeakObjectPtr<UAbilitySystemComponent> ASCWeakPtr;
	FGameplayAttribute AttributeToListenFor;
	
	void AttributeChanged(const FOnAttributeChangeData& Data);
};
