// Copyright GiftWrappedOdity


#include "GameObjects/SAS_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/SAS_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/SASTags.h"


ASAS_Projectile::ASAS_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	bReplicates = true; // set replication on server (replicated actor)
}

void ASAS_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	SpawnImpactEffects();
	
	// Overlapping actor (can be one of both characters)
	ASAS_PlayerCharacter* PlayerCharacter = Cast<ASAS_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;
	if (!PlayerCharacter->IsAlive()) return;
	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;
	
	// Apply GameplayEffect to Player
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	// dynamically set the damage using a TagSetByCallerMagnitude
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, SASTags::SetByCaller::Projectile, Damage);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); //applied on the overlapped actor
	// lifespan of actor BP is set in BP editor
	Destroy(); // destroy after impact
}

