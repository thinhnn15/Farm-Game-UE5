// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FishingWaterType.generated.h"

UENUM( BlueprintType )
enum class EFishingWaterType : uint8
{
    FreshWater UMETA( DisplayName = "Fresh Water" ), SaltWater UMETA( DisplayName = "Salt Water" ), BrackishWater UMETA( DisplayName = "Brackish Water" )
};
