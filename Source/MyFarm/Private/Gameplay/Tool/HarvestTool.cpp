// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/HarvestTool.h"

#include "Gameplay/Farm/FarmPlot.h"

bool UHarvestTool::CanUse( const FToolUseContext& UseContext ) const
{
    if ( !UseContext.HasValidHit() )
        return false;

    AFarmPlot* Plot = Cast< AFarmPlot >( UseContext.TargetActor );
    if ( !Plot )
        return false;

    return Plot->CanBeHarvested();
}

void UHarvestTool::Use( const FToolUseContext& UseContext )
{
    AFarmPlot* Plot = Cast< AFarmPlot >( UseContext.TargetActor );
    if ( !Plot )
        return;

    Plot->TryHarvest();
}
