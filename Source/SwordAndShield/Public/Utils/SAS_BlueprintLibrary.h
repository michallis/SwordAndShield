// Copyright Gift Wrapped Odity

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SAS_BlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection: uint8
{
	Left,
	Right,
	Front,
	Back
};

UCLASS()
class SWORDANDSHIELD_API USAS_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="SAS|Utils")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure, Category="SAS|Utils")
	static FName GetHitDirectionName(const EHitDirection HitDirection);
};
