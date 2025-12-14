// Copyright Gift Wrapped Odity


#include "Player/SAS_PlayerState.h"
#include "AbilitySystem/SAS_AbilitySystemComponent.h"
#include "AbilitySystem/SAS_AttributeSet.h"

ASAS_PlayerState::ASAS_PlayerState()
{
	// Netupdate frequency (default is too slow)
	SetNetUpdateFrequency(100.f); //high prio
	
	AbilitySystemComponent = CreateDefaultSubobject<USAS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<USAS_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASAS_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
