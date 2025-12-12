// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAndShield/Public/Characters/SAS_BaseCharacter.h"
#include "AbilitySystemComponent.h"

// Sets default values
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




