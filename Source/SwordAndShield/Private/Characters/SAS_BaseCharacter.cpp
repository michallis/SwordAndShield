// Copyright Gift Wrapped Odity


#include "SwordAndShield/Public/Characters/SAS_BaseCharacter.h"
#include "AbilitySystemComponent.h"

ASAS_BaseCharacter::ASAS_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ASAS_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr; //implemented in child instances
}

void ASAS_BaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	for (const auto& Ability : StartupAbilities)
	{
		//Ability light-weight wrapper
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

/**
 * Apply InitializeAttributes Effect on Self
 */
void ASAS_BaseCharacter::InitializeAttributes()
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set"))
	
	// GameContext and Effect Spec Handle is necessary before applying GameplayEffect (spec: lightweight versions)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);
	
	// Apply GameplayEffect
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}




