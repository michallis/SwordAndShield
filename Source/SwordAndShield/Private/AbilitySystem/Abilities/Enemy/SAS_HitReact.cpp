// Copyright Gift Wrapped Odity


#include "AbilitySystem/Abilities/Enemy/SAS_HitReact.h"


void USAS_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();
	ToInstigator = InstigatorLocation - AvatarLocation;
	ToInstigator.Normalize();
}
