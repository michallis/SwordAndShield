// Copyright GiftWrappedOdity


#include "GameObjects/SAS_Projectile.h"

#include "AbilitySystemComponent.h"
#include "Characters/SAS_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASAS_Projectile::ASAS_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	bReplicates = true; // set replication on server (replicated actor)
}

void ASAS_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	// Overlapping actor
	ASAS_PlayerCharacter* PlayerCharacter = Cast<ASAS_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter) && !PlayerCharacter->IsAlive()) return;
	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;
	
	// Apply GameplayEffect to Player
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// TODO: Use the damage variable for the amount of damage to cause 
	// lifespan of actor BP is set in BP editor
	Destroy(); // destroy after impact
}

