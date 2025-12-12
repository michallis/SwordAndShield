// Copyright Gift Wrapped Odity


#include "Player/SAS_PlayerState.h"
#include "AbilitySystemComponent.h"

ASAS_PlayerState::ASAS_PlayerState()
{
	// Netupdate frequency (default is too slow)
	SetNetUpdateFrequency(100.f); //high prio
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASAS_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
