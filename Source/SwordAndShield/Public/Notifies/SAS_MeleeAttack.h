// Copyright GiftWrappedOdity

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SAS_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class SWORDANDSHIELD_API USAS_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "SAS|Debugs")
	bool bDrawDebug = true;
	
	UPROPERTY(EditAnywhere, Category = "SAS|Socket")
	FName SocketName{"FX_Trail_01_R"};
	
	UPROPERTY(EditAnywhere, Category = "SAS|Socket")
	float SocketExtensionOffset{40.f};
	
	UPROPERTY(EditAnywhere, Category = "SAS|Socket")
	float SphereTraceRadius{40.f};
	
	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;
	
	void SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const;
};
