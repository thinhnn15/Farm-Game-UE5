// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Farm/FarmPlot.h"

#include "NiagaraFunctionLibrary.h"
#include "Gameplay/Crop/CropActor.h"
#include "Gameplay/Crop/CropInstance.h"
#include "Data/CropTypeData.h"
#include "Components/BoxComponent.h"
#include "Gameplay/Farm/FarmPlotVisualAsset.h"
#include "Gameplay/Farm/FarmPlotVisualData.h"


AFarmPlot::AFarmPlot()
{
    PrimaryActorTick.bCanEverTick = false;
    USceneComponent* Root = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );
    SetRootComponent( Root );
    // Collision (Root)
    PlotCollision = CreateDefaultSubobject< UBoxComponent >( TEXT( "PlotCollision" ) );
    PlotCollision->SetupAttachment( Root );

    PlotCollision->SetBoxExtent( FVector( 100.f, 100.f, 20.f ) );
    PlotCollision->SetRelativeLocation( FVector( 0.f, 0.f, 20.f ) );
    PlotCollision->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    PlotCollision->SetCollisionObjectType( ECC_WorldDynamic );

    PlotCollision->SetCollisionResponseToAllChannels( ECR_Ignore );
    PlotCollision->SetCollisionResponseToChannel( ECC_Visibility, ECR_Block );

    // Visual Mesh
    PlotMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "PlotMesh" ) );
    PlotMesh->SetupAttachment( PlotCollision );
    PlotMesh->SetRelativeLocation( FVector( 0.f, 0.f, 1.0f ) );

    PlotMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void AFarmPlot::BeginPlay()
{
    Super::BeginPlay();
}

void AFarmPlot::SetPlotState( EFarmPlotState NewState )
{
    if ( PlotState == NewState )
        return;
    PlotState = NewState;
    UpdatePlotVisuals();
}

void AFarmPlot::UpdatePlotVisuals()
{
    if ( !PlotVisualAsset || !PlotMesh )
        return;

    const FFarmPlotStateVisual* Visual = PlotVisualAsset->GetVisualForPlotState( PlotState );
    if ( !Visual )
        return;

    if ( Visual->SoilMaterial )
        PlotMesh->SetMaterial( 0, Visual->SoilMaterial );

    if ( Visual->EnterStateX )
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            Visual->EnterStateX,
            GetActorLocation()
        );

    // TNN-TODO: handle for highlight
}

bool AFarmPlot::CanPlant() const
{
    return PlotState == EFarmPlotState::Tilled;
}

bool AFarmPlot::PlantCrop( FName CropRowId )
{
    if ( CropRowId.IsNone() || !CanPlant() || !CropActorClass )
    {
        UE_LOG( LogTemp, Warning, TEXT("[FarmPlot] Cannot plant crop.") );
        return false;
    }
    SetPlotState( EFarmPlotState::Planted );
    ClearCrop();
    // Create Crop Instance (logic)
    CropInstance = NewObject< UCropInstance >( GetGameInstance() );
    CropInstance->Init( CropRowId );

    CropInstance->OnStageChanged.AddDynamic(
        this,
        &AFarmPlot::OnCropStageChanged
    );

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
    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Planted crop row: %s"), *CropRowId.ToString() );
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
    if ( !CanBeHarvested() )
        return false;

    if ( !CropInstance->TryHarvest() )
        return false;

    // If crop is not regrowable → clear plot
    if ( !CropInstance->IsAlive() )
    {
        SetPlotState( EFarmPlotState::Untilled );
        ClearCrop();
    }

    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Crop harvested.") );
    return true;
}

void AFarmPlot::Water()
{
    if ( !CanBeWatered() )
        return;

    SetPlotState( EFarmPlotState::Watered );
    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Watered.") );
}

bool AFarmPlot::CanBeTilled() const
{
    return PlotState == EFarmPlotState::Untilled;
}

void AFarmPlot::Till()
{
    if ( !CanBeTilled() )
        return;

    SetPlotState( EFarmPlotState::Tilled );
    UE_LOG( LogTemp, Log, TEXT("[FarmPlot] Tilled.") );
}

bool AFarmPlot::CanBeWatered() const
{
    return PlotState == EFarmPlotState::Planted;
}

bool AFarmPlot::CanBeHarvested() const
{
    return PlotState == EFarmPlotState::ReadyToHarvest;
}

void AFarmPlot::OnCropStageChanged( ECropGrowthStage NewStage )
{
    if ( NewStage == ECropGrowthStage::Harvestable )
        SetPlotState( EFarmPlotState::ReadyToHarvest );
}
