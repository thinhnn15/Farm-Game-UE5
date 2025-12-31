// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BugHabitatType.generated.h"

UENUM( BlueprintType )
enum class EBugHabitatType : uint8
{
    Grass UMETA( DisplayName="Grass" )
    , FarmLand UMETA( DisplayName="Farm Land" )
    , Forest UMETA( DisplayName="Forest" )
    , NearWater UMETA( DisplayName="Near Water" )
};
