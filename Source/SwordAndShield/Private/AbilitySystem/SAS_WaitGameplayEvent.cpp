// Copyright GiftWrappedOdity


#include "AbilitySystem/SAS_WaitGameplayEvent.h"

USAS_WaitGameplayEvent* USAS_WaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor,
	FGameplayTag EventTag, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	USAS_WaitGameplayEvent* MyObj = NewObject<USAS_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void USAS_WaitGameplayEvent::StartActivation()
{
	Activate();
}
