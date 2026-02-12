// Copyright GiftWrappedOdity


#include "AbilitySystem/Abilities/Enemy/SAS_SearchForTarget.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AbilitySystem/SAS_WaitGameplayEvent.h"
#include "Characters/SAS_EnemyCharacter.h"
#include "GameplayTags/SASTags.h"
#include "Tasks/AITask_MoveTo.h"
#include "Utils/SAS_BlueprintLibrary.h"


USAS_SearchForTarget::USAS_SearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void USAS_SearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 1. Cache Owning BP_SAS_EnemyBase and AI Controller
	OwningEnemy = Cast<ASAS_EnemyCharacter>(GetAvatarActorFromActorInfo());
	check(OwningEnemy.IsValid());
	OwningAIController = Cast<AAIController>(OwningEnemy->GetController());
	check(OwningAIController.IsValid());
	
	// 2. Start Search
	StartSearch();
	
	// 3. Wait for GameplayEventTask - create an instance and subscribe to delegate
	// We store a TObjectPtr in the interface, so that the instance is not GCd while the ability is active.
	// When the ability dies, the reference will be destroyed
	WaitGameplayEventTask = USAS_WaitGameplayEvent::WaitGameplayEventToActorProxy(GetAvatarActorFromActorInfo(), SASTags::Events::Enemy::EndAttack);
	WaitGameplayEventTask->EventReceived.AddDynamic(this, &ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
}

void USAS_SearchForTarget::StartSearch()
{
	if (bDrawDebugs) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("USAS_SearchForTarget::StartSearch")));
	if (!OwningEnemy.IsValid()) return;
	
	const float SearchDelay = FMath::RandRange(OwningEnemy->MinAttackDelay, OwningEnemy->MaxAttackDelay);
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, SearchDelay);
	SearchDelayTask->OnFinish.AddDynamic(this, &ThisClass::Search);
	SearchDelayTask->Activate();
}

void USAS_SearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	StartSearch();
}

void USAS_SearchForTarget::Search()
{
	// 1.Finding Closest Base Character (alive)
	const FVector SearchOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	FClosestActorWithTagResult ClosestActorResult = USAS_BlueprintLibrary::FindClosesActorWithTag(this, SearchOrigin, SasCustomTags::Player);
	TargetBaseCharacter = Cast<ASAS_BaseCharacter>(ClosestActorResult.Actor);
	
	// 2.Finding Closest Base Character (alive)
	if (!TargetBaseCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	if (TargetBaseCharacter->IsAlive())
	{
		MoveToTargetAndAttack();
	} else
	{
		StartSearch();
	}
}

void USAS_SearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemy.IsValid() || !OwningAIController.IsValid() || !TargetBaseCharacter.IsValid()) return;
	if (!OwningEnemy->IsAlive())
	{
		StartSearch();
		return;
	}
	
	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(
		OwningAIController.Get(), 
		FVector(), 
		TargetBaseCharacter.Get(), 
		OwningEnemy->AcceptanceRadius);
	
	// Subscribe, no activation call, but a ConditionalPerformMove
	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this, &ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
}

void USAS_SearchForTarget::AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (Result != EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	
	OwningEnemy->RotateToTarget(TargetBaseCharacter.Get());
	// Wait while rotating to target and then call Attack
	AttackDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, OwningEnemy->GetTimelineLength());
	AttackDelayTask->OnFinish.AddDynamic(this, &ThisClass::Attack);
	AttackDelayTask->Activate();
}

void USAS_SearchForTarget::Attack()
{
	const FGameplayTag AttackTag = SASTags::SASAbilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
	
}
