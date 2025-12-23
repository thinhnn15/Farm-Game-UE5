// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Public/Gameplay/Crop/CropVisualData.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropTypeRow.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FCropTypeRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Identity
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    FName CropId;

    // Growth
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    int32 TotalGrowthDays = 1;

    // Day -> Stage
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    TMap< int32, ECropGrowthStage > GrowthStages;

    // Harvest
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    bool bRegrowable = false;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( EditCondition = "bRegrowable" ) )
    int32 RegrowDays = 0;

    // Visuals
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    TObjectPtr< UCropVisualData > CropVisualData;
};
