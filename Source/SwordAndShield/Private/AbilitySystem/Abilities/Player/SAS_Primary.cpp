// Copyright Gift Wrapped Odity


#include "AbilitySystem/Abilities/Player/SAS_Primary.h"

#include "Engine/OverlapResult.h"

void USAS_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	//Overlap test - ensure that the overlap test ignores the Avatar actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	// Cannot be done in Blueprints? BlockAll by default normally (using check interfaces)
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	// Not hit result as start and end of trace is same -> overlap is enough
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
	
	if (bDrawDebugs){
		DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
		for (const FOverlapResult& Overlap : OverlapResults)
		{
			if (IsValid(Overlap.GetActor()))
			{
				FVector DebugLocation = Overlap.GetActor()->GetActorLocation();
				DebugLocation.Z += 100.f;
				DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 16, FColor::Green, false, 3.f);
			}
		}
	}
}
