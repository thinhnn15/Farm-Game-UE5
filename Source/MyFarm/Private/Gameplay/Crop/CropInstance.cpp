// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"

void UCropInstance::Init( UCropTypeData* InCropTypeData )
{
    CropData = InCropTypeData;
    DaysGrown = 0;
    CurrentGrowthStage = ECropGrowthStage::Seed;
}

void UCropInstance::OnDayAdvanced( int32 NewDay )
{
    if ( !CropData )
        return;

    DaysGrown++;
    // Determine stage from data
    const ECropGrowthStage NewStage = CropData->GetStageForDay( DaysGrown );

    if ( NewStage == CurrentGrowthStage )
        return;

    CurrentGrowthStage = NewStage;
    UE_LOG( LogTemp, Log,
            TEXT("[CropInstance] %s advanced to stage %d at day %d"),
            *GetNameSafe(CropData),
            (int32)CurrentGrowthStage,
            DaysGrown
    );
}
