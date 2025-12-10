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
	
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
	
};
