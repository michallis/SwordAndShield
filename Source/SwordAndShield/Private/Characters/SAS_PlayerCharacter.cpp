// Copyright Gift Wrapped Odity


#include "SwordAndShield/Public/Characters/SAS_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/SAS_AttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/SAS_PlayerState.h"


ASAS_PlayerCharacter::ASAS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	// Setup Player CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	// Setup Player FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* ASAS_PlayerCharacter::GetAbilitySystemComponent() const
{
	ASAS_PlayerState* SASPlayerState = Cast<ASAS_PlayerState>(GetPlayerState());
	if (!IsValid(SASPlayerState)) return nullptr;
	return SASPlayerState->GetAbilitySystemComponent();
}

UAttributeSet* ASAS_PlayerCharacter::GetAttributeSet() const
{
	ASAS_PlayerState* SASPlayerState = Cast<ASAS_PlayerState>(GetPlayerState());
	if (!IsValid(SASPlayerState)) return nullptr;
	
	return SASPlayerState->GetAttributeSet();
}

/**
 * Necessary for the SERVER to Init the ability system
 * It's sufficient to give startup abilities on the server
 * as they will be replicated across clients
 * Here we initialize Gameplay Attributes as well
 */
void ASAS_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();
	
	// Get Attribute set - delegate for Health attribute
	USAS_AttributeSet* AttributeSet = Cast<USAS_AttributeSet>(GetAttributeSet());
	if (!IsValid(AttributeSet)) return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged );
}

/**
 * Necessary for the CLIENT to Init the ability system
 * After the player character has been replicated, the event is thrown on the client
 */
void ASAS_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	// Get Attribute set - delegate for Health attribute
	USAS_AttributeSet* SAS_AttributeSet = Cast<USAS_AttributeSet>(GetAttributeSet());
	if (!IsValid(SAS_AttributeSet)) return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(SAS_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged );
}

