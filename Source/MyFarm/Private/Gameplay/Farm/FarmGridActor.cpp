// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Farm/FarmGridActor.h"


// Sets default values
AFarmGridActor::AFarmGridActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AFarmGridActor::BeginPlay()
{
    Super::BeginPlay();

    if ( !PlotClass )
        return;
    constexpr float PlotGroundOffsetZ = -20.f;

    FVector Origin = GetActorLocation();
    for ( int32 Row = 0; Row < Rows; ++Row )
    {
        for ( int32 Col = 0; Col < Columns; ++Col )
        {
            FVector SpawnLocation = Origin;
            SpawnLocation.X += Row * PlotSpacing;
            SpawnLocation.Y += Col * PlotSpacing;
            SpawnLocation.Z += PlotGroundOffsetZ;
            GetWorld()->SpawnActor< AFarmPlot >( PlotClass, SpawnLocation, FRotator::ZeroRotator );
        }
    }
}
