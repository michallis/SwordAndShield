// Copyright Gift Wrapped Odity


#include "Tasks/SAS_AttributeChangeTask.h"
#include "AbilitySystemComponent.h"

USAS_AttributeChangeTask* USAS_AttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAttribute Attribute)
{
	USAS_AttributeChangeTask* WaitForAttributeChangeTask = NewObject<USAS_AttributeChangeTask>();
	WaitForAttributeChangeTask->ASCWeakPtr = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;
	
	if (!IsValid(AbilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}
	
	// Register a listener
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &USAS_AttributeChangeTask::AttributeChanged);
	return WaitForAttributeChangeTask;
}

/**
 * Cleanup resources
 * Remove all listen objects on the ASC
 */
void USAS_AttributeChangeTask::EndTask()
{
	if (ASCWeakPtr.IsValid())
	{
		ASCWeakPtr->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USAS_AttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}

