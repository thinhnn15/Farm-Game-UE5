// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/WateringTool.h"

#include "Gameplay/Farm/FarmPlot.h"

bool UWateringTool::CanUseOnActor( AActor* TargetActor ) const
{
    if ( !TargetActor )
        return false;
    // Watering tool can only be used on FarmPlot
    return Cast< AFarmPlot >( TargetActor ) != nullptr;
}

void UWateringTool::UseOnActor( AActor* TargetActor )
{
    AFarmPlot* FarmPlot = Cast< AFarmPlot >( TargetActor );
    if ( !FarmPlot )
        return;
    
    UE_LOG( LogTemp, Log, TEXT( "[WateringTool] Used watering tool on FarmPlot: %s" ), *FarmPlot->GetName() );
    // Delegate watering logic to the farm plot
    FarmPlot->Water();
}
