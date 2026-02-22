// Copyright Gift Wrapped Odity


#include "Utils/SAS_BlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SAS_AttributeSet.h"
#include "Characters/SAS_BaseCharacter.h"
#include "GameplayTags/SASTags.h"
#include "Kismet/GameplayStatics.h"

EHitDirection USAS_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		// Either left or right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Front;
}

FName USAS_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Front: return FName("Front");
		case EHitDirection::Back: return FName("Back");
		default: return FName("None");
	}
}

FClosestActorWithTagResult USAS_BlueprintLibrary::FindClosesActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);
	
	// search the closest one
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		// avoid running to death character
		ASAS_BaseCharacter* BaseCharacter = Cast<ASAS_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;
		
		// distance
		const float Distance = FVector::Dist(Origin, Actor->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}
	
	return FClosestActorWithTagResult{ClosestActor, ClosestDistance};
}


void USAS_BlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem)
{
	ASAS_BaseCharacter* PlayerCharacter = Cast<ASAS_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter)) return;
	if (!PlayerCharacter->IsAlive()) return;
	
	USAS_AttributeSet* AttributeSet = Cast<USAS_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet)) return;
	
	// Send HitReact or Death event
	const bool bLethal = AttributeSet->GetHealth() - Damage <= 0;
	const FGameplayTag EventTag = bLethal ? SASTags::Events::Player::Death : SASTags::Events::Player::HitReact;
	
	// Enrich the payload with an optional field
	Payload.OptionalObject = OptionalParticleSystem;
	
	// Send Gameplay Event to Actor
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter, EventTag, Payload);
	
	// Do damage with SetByCaller Magnitude
	UAbilitySystemComponent* TargetASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC)) return;
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DataTag, -Damage);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
