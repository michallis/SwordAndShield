// Copyright Gift Wrapped Odity


#include "SwordAndShield/Public/Characters/SAS_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

namespace SasCustomTags
{
	const FName Player = FName("Player");
}

ASAS_BaseCharacter::ASAS_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

/**
 * Necessary as we have marked the bAlive attribute as replicated
 * @param OutLifetimeProps 
 */
void ASAS_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, bAlive);
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
	ExecuteGameplayEffect(InitializeAttributesEffect);
}

void ASAS_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChange)
{
	if (AttributeChange.NewValue <= 0.f)
	{
		HandleDeath(); //can be overriden by children
	}
}

void ASAS_BaseCharacter::HandleDeath()
{
	bAlive = false;
	/*if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s has died."), *GetName()));
	}*/
}


void ASAS_BaseCharacter::HandleRespawn()
{
	bAlive = true;
}

void ASAS_BaseCharacter::ResetAttributes()
{
	ExecuteGameplayEffect(ResetAttributesEffect);
}


/**
 * Utility function to send out GameplayEffects where needed
 * @param GameplayEffect 
 */
void ASAS_BaseCharacter::ExecuteGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect)
{
	checkf(IsValid(GameplayEffect), TEXT("ResetAttributesEffect not set"))
	
	// GameContext and Effect Spec Handle is necessary before applying GameplayEffect (spec: lightweight versions)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, 1.f, ContextHandle);
	
	// Apply GameplayEffect
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}


