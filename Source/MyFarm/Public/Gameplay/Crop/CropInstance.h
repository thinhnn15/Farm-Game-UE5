// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Gameplay/Instance/GameplayInstanceBase.h"
#include "Public/Core/Time/DayAdvanceListener.h"
#include "Public/Data/CropTypeData.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCropStageChanged, ECropGrowthStage, NewStage );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCropHarvested );

UCLASS( BlueprintType )
class MYFARM_API UCropInstance : public UGameplayInstanceBase,
                                 public IDayAdvanceListener
{
    GENERATED_BODY()

public:
    UPROPERTY( BlueprintAssignable, Category = "Crop" )
    FOnCropStageChanged OnStageChanged;
    
    UPROPERTY( BlueprintAssignable, Category = "Crop" )
    FOnCropHarvested OnHarvested;
    
    UFUNCTION( BlueprintCallable, Category = "Crop" )
    bool TryHarvest();
    /*------------- Lifecycle -------------*/
    void Init( UCropTypeData* InCropTypeData );
    virtual void OnInitialize() override;
    virtual void OnDeinitialize() override;
    /*------------- Time -------------*/
    // IDayAdvanceListener interface
    virtual void OnDayAdvanced( int32 NewDay ) override;

    /*------------- Stage -------------*/
    ECropGrowthStage GetCurrentStage() const;
    UCropTypeData* GetCropData() const;
    
    /*------------- Harvest -------------*/
    bool CanHarvest() const;
    bool Harvest();
protected:
    /*------------- Internal -------------*/
    void UpdateGrowthStage();
    void EnterRegrow();
    
protected:
    UPROPERTY()
    TObjectPtr< UCropTypeData > CropData;

    UPROPERTY()
    int32 DaysGrown = 0;

    UPROPERTY()
    ECropGrowthStage CurrentStage = ECropGrowthStage::Seed;
};
