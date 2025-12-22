// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Farm/FarmPlot.h"
#include "Public/Gameplay/Crop/CropActor.h"
#include "Public/Gameplay/Crop/CropInstance.h"
#include "Public/Data/CropTypeData.h"


AFarmPlot::AFarmPlot()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AFarmPlot::BeginPlay()
{
    Super::BeginPlay();
}

bool AFarmPlot::CanPlant() const
{
    return CropInstance == nullptr;
}

bool AFarmPlot::PlantCrop( UCropTypeData* CropType )
{
    if ( !CropType || !CanPlant() || !CropActorClass )
    {
        UE_LOG( LogTemp, Warning, TEXT("[FarmPlot] Cannot plant crop.") );
        return false;
    }
    // Create Crop Instance (logic)
    CropInstance = NewObject< UCropInstance >( GetGameInstance() );
    CropInstance->Init( CropType );

    // Spawn Crop Actor (visual)
    FActorSpawnParameters Params;
    Params.Owner = this;

    FVector SpawnLocation = GetActorLocation();
    SpawnLocation.Z += 10.f;

    CropActor = GetWorld()->SpawnActor< ACropActor >(
        CropActorClass,
        SpawnLocation,
        FRotator::ZeroRotator,
        Params
    );

    if ( !CropActor )
    {
        UE_LOG( LogTemp, Warning, TEXT("[FarmPlot] Failed to spawn crop.") );
        CropInstance = nullptr;
        return false;
    }

    // Bind logic -> visual
    CropActor->BindCropInstance( CropInstance );
    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Planted crop: %s"), *GetNameSafe(CropType) );
    return true;
}

bool AFarmPlot::TryHarvest()
{
    if ( !CropInstance )
        return false;

    if ( !CropInstance->TryHarvest() )
        return false;

    // Cleanup visual
    if ( CropActor )
    {
        CropActor->Destroy();
        CropActor = nullptr;
    }
    // Cleanup logic
    CropInstance = nullptr;

    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Crop harvested successfully.") );
    return true;
}
