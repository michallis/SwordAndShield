// Copyright Gift Wrapped Odity


#include "AbilitySystem/SAS_AbilitySystemComponent.h"

#include "GameplayTags/SASTags.h"

// Will not work for abilities given locally -> use repNotify
void USAS_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	HandleAutoActivatedAbility(AbilitySpec);
}

void USAS_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	// We need to lock the scope - abilities are moving dynamically
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec  : GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

void USAS_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;
	for (const FGameplayTag& Tag : AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(SASTags::SASAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			//GiveAbilityAndActivateOnce(AbilitySpec); //removed after activation
			return;
		}
	}
}
