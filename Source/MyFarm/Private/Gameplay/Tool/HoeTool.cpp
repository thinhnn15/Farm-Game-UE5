// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/HoeTool.h"

#include "Gameplay/Farm/FarmPlot.h"

bool UHoeTool::CanUse( const FToolUseContext& UseContext ) const
{
    if ( !UseContext.HasValidHit() )
        return false;

    AFarmPlot* Plot = Cast< AFarmPlot >( UseContext.TargetActor );
    if ( !Plot )
        return false;

    return Plot->CanBeTilled();
}

void UHoeTool::Use( const FToolUseContext& Context )
{
    AFarmPlot* Plot = Cast< AFarmPlot >( Context.TargetActor );
    if ( !Plot )
        return;
    
    return Plot->Till();
}
