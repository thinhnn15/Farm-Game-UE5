// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CropGrowthStage.generated.h"

UENUM(BlueprintType)
enum class ECropGrowthStage : uint8
{
    Seed        UMETA(DisplayName = "Seed"),
    Growing     UMETA(DisplayName = "Growing"),
    Mature      UMETA(DisplayName = "Mature"),
    Harvestable UMETA(DisplayName = "Harvestable"),
    Dead        UMETA(DisplayName = "Dead")
};
