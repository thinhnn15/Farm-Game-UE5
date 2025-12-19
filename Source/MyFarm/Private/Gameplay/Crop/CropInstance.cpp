// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"

void UCropInstance::Init( UCropTypeData* InCropTypeData )
{
    CropData = InCropTypeData;
    DaysGrown = 0;
    CurrentStage = ECropGrowthStage::Seed;
}

void UCropInstance::OnDayAdvanced( int32 NewDay )
{
    if ( !CropData )
        return;

    DaysGrown++;
    // Determine stage from data
    const ECropGrowthStage NewStage = CropData->GetStageForDay( DaysGrown );

    if ( NewStage == CurrentStage )
        return;

    CurrentStage = NewStage;
    UE_LOG( LogTemp, Log,
            TEXT("[CropInstance] %s advanced to stage %d at day %d"),
            *GetNameSafe(CropData),
            (int32)CurrentStage,
            DaysGrown
    );
    OnStageChanged.Broadcast( CurrentStage );
}

ECropGrowthStage UCropInstance::GetCurrentStage() const
{
    return CurrentStage;
}

void UCropInstance::OnInitialize()
{
    DaysGrown = 0;
    CurrentStage = ECropGrowthStage::Seed;
}
