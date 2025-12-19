// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTypeData.h"
#include "GameplayTypeData.h"
#include "../Gameplay/Crop/CropGrowthStage.h"
#include "CropTypeData.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UCropTypeData : public UGameplayTypeData
{
    GENERATED_BODY()
    
public:
    // Total days needed to reach mature stage
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Growth" )
    int32 TotalGrowthDays = 1;
    
    // Growth stages threshold ( day -> stage )
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Growth" )
    TMap< int32, ECropGrowthStage > GrowthStages;
    
    // Can this crop be harvested multiple times
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Harvest" )
    bool bRegrowable = false;
    
    // Days to regrow after harvest
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Harvest", meta = ( EditCondition = "bRegrowable" ) )
    int32 RegrowDays = 1;
};
