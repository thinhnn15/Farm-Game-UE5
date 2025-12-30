// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmPlot.h"
#include "Engine/DataAsset.h"
#include "FarmPlotVisualData.h"
#include "FarmPlotVisualAsset.generated.h"

/**
 * 
 */
UCLASS( BlueprintType )
class MYFARM_API UFarmPlotVisualAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    TMap< EFarmPlotState, FFarmPlotStateVisual > StateVisualMap;
    
    const FFarmPlotStateVisual* GetVisualForPlotState( EFarmPlotState PlotState ) const;
};
