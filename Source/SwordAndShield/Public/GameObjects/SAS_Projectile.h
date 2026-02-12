// Copyright GiftWrappedOdity

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SAS_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class SWORDANDSHIELD_API ASAS_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASAS_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SAS|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{10.f};
	
	UFUNCTION(BlueprintImplementableEvent, Category="SAS|Projectile")
	void SpawnImpactEffects();

private:
	UPROPERTY(VisibleAnywhere, Category="SAS|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
