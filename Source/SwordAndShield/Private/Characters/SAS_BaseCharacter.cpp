// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAndShield/Public/Characters/SAS_BaseCharacter.h"


// Sets default values
ASAS_BaseCharacter::ASAS_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}




