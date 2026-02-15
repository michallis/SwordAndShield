// Copyright Gift Wrapped Odity


#include "Player/SAS_PlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/SASTags.h"
#include "Kismet/GameplayStatics.h"

void ASAS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (!IsValid(InputSubsystem)) return;
	for (UInputMappingContext* Context: InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Sprint);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Crouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Canceled, this, &ThisClass::CrouchReset);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ThisClass::CrouchReset);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ThisClass::SprintReset);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::SprintReset);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &ThisClass::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this, &ThisClass::Tertiary);
	
}

void ASAS_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	GetCharacter()->Jump();
}

void ASAS_PlayerController::Crouch()
{
	//done in BP
}

void ASAS_PlayerController::CrouchReset()
{
	//done in BP
}

void ASAS_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	GetCharacter()->StopJumping();
}

// TODO
void ASAS_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	// Get player camera manager
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);
	if (!IsValid(CameraManager)) return;
	
	// get control rotation
	const FRotator ControlRot = GetControlRotation();
	const FRotator CameraRot = CameraManager->GetCameraRotation();
	
	// Find which way is forward
	const FRotator YawRotation(0.f, CameraRot.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y, false);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X, false);
}

void ASAS_PlayerController::Sprint()
{
	if (!IsValid(GetCharacter())) return;
	if (bIsSliding)
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxSpeedMovementSlide;
	}else
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxSpeedMovementSprint;	
	}
	
}

void ASAS_PlayerController::SprintReset()
{
	if (!IsValid(GetCharacter())) return;
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxSpeedMovementWalk;
}

void ASAS_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ASAS_PlayerController::Primary()
{
	ActivateAbility(SASTags::SASAbilities::Primary);
}

void ASAS_PlayerController::Secondary()
{
	ActivateAbility(SASTags::SASAbilities::Secondary);
}

void ASAS_PlayerController::Tertiary()
{
	ActivateAbility(SASTags::SASAbilities::Tertiary);
}

void ASAS_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
	
}
