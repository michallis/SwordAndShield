// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "SAS_BaseCharacter.generated.h"

UCLASS(Abstract)
class SWORDANDSHIELD_API ASAS_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASAS_BaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	void GiveStartupAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category="SAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};
