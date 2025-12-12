// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "SAS_BaseCharacter.h"
#include "SAS_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SWORDANDSHIELD_API ASAS_PlayerCharacter : public ASAS_BaseCharacter
{
	GENERATED_BODY()

public:
	ASAS_PlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
};
