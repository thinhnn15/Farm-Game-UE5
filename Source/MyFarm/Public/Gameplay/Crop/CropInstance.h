// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Gameplay/Instance/GameplayInstanceBase.h"
#include "Public/Core/Time/DayAdvanceListener.h"
#include "Public/Data/CropTypeData.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropInstance.generated.h"


UCLASS()
class MYFARM_API UCropInstance : public UGameplayInstanceBase,
                                 public IDayAdvanceListener
{
    GENERATED_BODY()

public:
    void Init( UCropTypeData* InCropTypeData );
    
    // IDayAdvanceListener interface
    virtual void OnDayAdvanced( int32 NewDay ) override;
    
    ECropGrowthStage GetCurrentGrowthStage() const;
    
private:
    UPROPERTY()
    TObjectPtr<UCropTypeData> CropData;
    
    UPROPERTY()
    int32 DaysGrown = 0;
    
    UPROPERTY()
    ECropGrowthStage CurrentGrowthStage = ECropGrowthStage::Seed;
};
