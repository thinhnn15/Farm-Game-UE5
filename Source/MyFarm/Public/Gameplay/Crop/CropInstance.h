// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Gameplay/Instance/GameplayInstanceBase.h"
#include "Public/Core/Time/DayAdvanceListener.h"
#include "Public/Data/CropTypeData.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCropStageChanged, ECropGrowthStage, NewStage );

UCLASS( BlueprintType )
class MYFARM_API UCropInstance : public UGameplayInstanceBase,
                                 public IDayAdvanceListener
{
    GENERATED_BODY()

public:
    UPROPERTY( BlueprintAssignable, Category = "Crop" )
    FOnCropStageChanged OnStageChanged;

    void Init( UCropTypeData* InCropTypeData );

    // IDayAdvanceListener interface
    virtual void OnDayAdvanced( int32 NewDay ) override;

    ECropGrowthStage GetCurrentStage() const;
    
    UCropTypeData* GetCropData() const;

protected:
    UPROPERTY()
    TObjectPtr< UCropTypeData > CropData;

    UPROPERTY()
    int32 DaysGrown = 0;

    UPROPERTY()
    ECropGrowthStage CurrentStage = ECropGrowthStage::Seed;
    
    virtual void OnInitialize() override;
};
