// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/HandTool.h"

#include "Gameplay/Farm/FarmPlot.h"

void UHandTool::Use( const FToolUseContext& Context )
{
    AFarmPlot* Plot = Cast< AFarmPlot >( Context.TargetActor );
    if ( !Plot )
        return;
    // Plot->Interact( Context );
}
