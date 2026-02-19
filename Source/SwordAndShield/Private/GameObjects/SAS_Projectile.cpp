// Copyright GiftWrappedOdity


#include "GameObjects/SAS_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/SAS_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/SASTags.h"
#include "Utils/SAS_BlueprintLibrary.h"


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
	FGameplayEventData Payload;
	Payload.Instigator = GetOwner();
	Payload.Target = PlayerCharacter;
	USAS_BlueprintLibrary::SendDamageEventToPlayer(PlayerCharacter, DamageEffect, Payload, SASTags::SetByCaller::Projectile, Damage);
	
	// lifespan of actor BP is set in BP editor
	Destroy(); // destroy after impact
}

