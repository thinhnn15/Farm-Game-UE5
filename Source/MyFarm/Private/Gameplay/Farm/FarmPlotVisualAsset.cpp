// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Farm/FarmPlotVisualAsset.h"

const FFarmPlotStateVisual* UFarmPlotVisualAsset::GetVisualForPlotState( EFarmPlotState PlotState ) const
{
    return StateVisualMap.Find( PlotState );
}
