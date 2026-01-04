// Copyright Gift Wrapped Odity


#include "Characters/SAS_EnemyCharacter.h"
#include "AbilitySystem/SAS_AbilitySystemComponent.h"
#include "AbilitySystem/SAS_AttributeSet.h"
#include "Runtime/AIModule/Classes/AIController.h"

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

UAttributeSet* ASAS_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ASAS_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	// Only on the server
	if (!HasAuthority()) return;
	GiveStartupAbilities();
	InitializeAttributes();
	
	// Get Attribute set - delegate for Health attribute
	USAS_AttributeSet* SAS_AttributeSet = Cast<USAS_AttributeSet>(GetAttributeSet());
	if (!IsValid(SAS_AttributeSet)) return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(SAS_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged );
}

void ASAS_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath(); // sets bAlive to false
	AAIController* AIController = GetController<AAIController>();
	if (!IsValid(AIController)) return;
	AIController->StopMovement();
}

