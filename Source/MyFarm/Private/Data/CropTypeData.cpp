// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Data/CropTypeData.h"

ECropGrowthStage UCropTypeData::GetStageForDay( int32 DaysGrown ) const
{
    ECropGrowthStage ResultStage = ECropGrowthStage::Seed;

    TArray< int32 > Keys;
    GrowthStages.GetKeys( Keys );
    Keys.Sort();

    for ( int32 DayThreshold : Keys )
    {
        if ( DaysGrown >= DayThreshold )
        {
            ResultStage = GrowthStages[ DayThreshold ];
        }
    }

    return ResultStage;
}

const FCropStageVisual* UCropTypeData::GetVisualForStage( ECropGrowthStage Stage ) const
{
    return StageVisuals.Find( Stage );
}

bool UCropTypeData::IsRegrowable() const
{
    return bRegrowable;
}

int32 UCropTypeData::GetRegrowDays() const
{
    return RegrowDays;
}

UCropVisualData* UCropTypeData::GetVisualData() const
{
    return VisualData;
}
