// Copyright GiftWrappedOdity

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SAS_GameplayAbility.h"
#include "SAS_SearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class ASAS_BaseCharacter;
class USAS_WaitGameplayEvent;
class ASAS_EnemyCharacter;
class AAIController;
class UAbilityTask_WaitDelay;
class UAITask_MoveTo;
class USAS_WaitGameplayEvent;

UCLASS()
class SWORDANDSHIELD_API USAS_SearchForTarget : public USAS_GameplayAbility
{
	GENERATED_BODY()
public:
	USAS_SearchForTarget();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	TWeakObjectPtr<ASAS_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<ASAS_BaseCharacter> TargetBaseCharacter;
	
	
private:
	UPROPERTY()
	TObjectPtr<USAS_WaitGameplayEvent> WaitGameplayEventTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;
	
	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;
	
	void StartSearch();
	
	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void Search();
	
	UFUNCTION()
	void AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);
	
	UFUNCTION()
	void Attack();
	
	void MoveToTargetAndAttack();
};
