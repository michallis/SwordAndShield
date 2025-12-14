// Copyright Gift Wrapped Odity


#include "Characters/SAS_EnemyCharacter.h"
#include "AbilitySystem/SAS_AbilitySystemComponent.h"
#include "AbilitySystem/SAS_AttributeSet.h"

ASAS_EnemyCharacter::ASAS_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<USAS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<USAS_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASAS_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASAS_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	// Only on the server
	if (!HasAuthority()) return;
	GiveStartupAbilities();
}
