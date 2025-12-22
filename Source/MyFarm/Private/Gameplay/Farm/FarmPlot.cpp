// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Farm/FarmPlot.h"
#include "Public/Gameplay/Crop/CropActor.h"
#include "Public/Gameplay/Crop/CropInstance.h"
#include "Public/Data/CropTypeData.h"
#include "Public/Data/CropTypeData.h"
#include "Components/BoxComponent.h"


AFarmPlot::AFarmPlot()
{
    PrimaryActorTick.bCanEverTick = false;

    // Collision (Root)
    PlotCollision = CreateDefaultSubobject< UBoxComponent >( TEXT( "PlotCollision" ) );
    SetRootComponent( PlotCollision );

    PlotCollision->SetBoxExtent( FVector( 100.f, 100.f, 20.f ) );
    PlotCollision->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    PlotCollision->SetCollisionObjectType( ECC_WorldDynamic );

    PlotCollision->SetCollisionResponseToAllChannels( ECR_Ignore );
    PlotCollision->SetCollisionResponseToChannel( ECC_Visibility, ECR_Block );

    // Visual Mesh
    PlotMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "PlotMesh" ) );
    PlotMesh->SetupAttachment( PlotCollision );

    PlotMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
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
    ClearCrop();
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

void AFarmPlot::ClearCrop()
{
    if ( CropActor )
    {
        CropActor->Destroy();
        CropActor = nullptr;
    }

    if ( CropInstance )
    {
        CropInstance->DeinitializeInstance();
        CropInstance = nullptr;
    }
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
