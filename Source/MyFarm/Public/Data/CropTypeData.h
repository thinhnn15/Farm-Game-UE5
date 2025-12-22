// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTypeData.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "Public/Gameplay/Crop/CropVisualData.h"
#include "CropTypeData.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UCropTypeData : public UGameplayTypeData
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure, Category = "Crop|Growth" )
    ECropGrowthStage GetStageForDay( int32 DaysGrown ) const;
    
    UFUNCTION( BlueprintPure, Category = "Crop|Growth" )
    int32 GetTotalGrowthDays() const;
    
    // Visual representation for a given growth stage
    const FCropStageVisual* GetVisualForStage(
        ECropGrowthStage Stage
    ) const;
    
    // Harvest
    UFUNCTION( BlueprintPure, Category = "Crop|Harvest" )
    bool IsRegrowable() const;
    
    UFUNCTION( BlueprintPure, Category = "Crop|Harvest" )
    int32 GetRegrowDays() const;
    
    // Get Visual Data
    UFUNCTION( BlueprintPure, Category = "Crop|Visual" )
    UCropVisualData* GetVisualData() const;   
    
    // Can harvest at stage
    UFUNCTION( BlueprintPure, Category = "Crop|Visual" )
    bool CanHarvestAtStage(ECropGrowthStage Stage) const;
protected:
    // Total days needed to reach mature stage
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Growth" )
    int32 TotalGrowthDays = 1;

    // Growth stages threshold ( day -> stage )
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Growth" )
    TMap< int32, ECropGrowthStage > GrowthStages;
    
    UPROPERTY(EditDefaultsOnly, Category = "Visual")
    TMap< ECropGrowthStage, FCropStageVisual > StageVisuals;

    // Can this crop be harvested multiple times
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Harvest" )
    bool bRegrowable = false;

    // Days to regrow after harvest
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Harvest", meta = ( EditCondition = "bRegrowable" ) )
    int32 RegrowDays = 1;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    TObjectPtr< UCropVisualData > VisualData;
};
