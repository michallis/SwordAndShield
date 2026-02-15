// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "SAS_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class SWORDANDSHIELD_API ASAS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(BlueprintReadWrite, Category="SAS|Movement")
	float MaxSpeedMovementWalk = 200.f;
	
	UPROPERTY(BlueprintReadWrite, Category="SAS|Movement")
	float MaxSpeedMovementSprint = 400.f;
	
	UPROPERTY(BlueprintReadWrite, Category="SAS|Movement")
	float SlideDuration = 0.5f;
	
	UPROPERTY(BlueprintReadWrite, Category="SAS|Movement")
	float MaxSpeedMovementSlide = 480.f;
	
	UPROPERTY(BlueprintReadWrite, Category="SAS|Movement")
	bool bIsSliding = false;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Movement")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Movement")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Abilities")
	TObjectPtr<UInputAction> SecondaryAction;
	
	UPROPERTY(EditDefaultsOnly, Category="SAS|Input|Abilities")
	TObjectPtr<UInputAction> TertiaryAction;
	
	// Movement
	void Jump();
	void Crouch();
	void CrouchReset();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Sprint();
	void SprintReset();
	void Look(const FInputActionValue& Value);
	
	// Abilities
	void Primary();
	void Secondary();
	void Tertiary();
	
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
	
};
