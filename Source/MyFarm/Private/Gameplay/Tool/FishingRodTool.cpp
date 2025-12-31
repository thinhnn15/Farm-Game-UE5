// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/FishingRodTool.h"

#include "Gameplay/Fishing/FishingSpot.h"

bool UFishingRodTool::CanUse( const FToolUseContext& UseContext ) const
{
    return Cast< AFishingSpot >( UseContext.TargetActor ) != nullptr;
}

void UFishingRodTool::Use( const FToolUseContext& UseContext )
{
    AFishingSpot* Spot = Cast< AFishingSpot >( UseContext.TargetActor );
    if ( !Spot )
        return;
    
    Spot->StartFishing( UseContext.InstigatorController );
}
