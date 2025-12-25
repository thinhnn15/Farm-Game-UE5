// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/WateringTool.h"
#include "Gameplay/Tool/ToolUseContext.h"
#include "Gameplay/Farm/FarmPlot.h"

bool UWateringTool::CanUse( const FToolUseContext& UseContext ) const
{
    if ( !UseContext.TargetActor )
        return false;

    return Cast< AFarmPlot >( UseContext.TargetActor ) != nullptr;
}

void UWateringTool::Use( const FToolUseContext& Context )
{
    if ( Context.TargetActor )
        return;
    AFarmPlot* Plot = Cast< AFarmPlot >( Context.TargetActor );
    if ( !Plot )
        return;
    
    Plot->Water();
}
