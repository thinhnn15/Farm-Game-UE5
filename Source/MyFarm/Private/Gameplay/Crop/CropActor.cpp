// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropActor.h"

#include "NiagaraFunctionLibrary.h"
#include "Public/Gameplay/Crop/CropInstance.h"
#include "Public/Data/CropTypeData.h"
#include "Components/StaticMeshComponent.h"


ACropActor::ACropActor()
{
    Root = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );
    SetRootComponent( Root );

    MeshComponent = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "CropMesh" ) );
    RootComponent = MeshComponent;

    MeshComponent->SetMobility( EComponentMobility::Movable );
    MeshComponent->SetVisibility( true );
    MeshComponent->SetHiddenInGame( false );
}

void ACropActor::BeginPlay()
{
    Super::BeginPlay();
}

void ACropActor::BindCropInstance( UCropInstance* InCropInstance )
{
    if ( !InCropInstance )
        return;

    CropInstance = InCropInstance;

    if ( UCropTypeData* CropType = CropInstance->GetCropData() )
    {
        CropVisualData = CropType->GetVisualData();
    }

    // Bind to stage change event
    CropInstance->OnStageChanged.AddDynamic( this, &ACropActor::OnCropStageChanged );

    // Apply initial visual
    ApplyStageVisuals( CropInstance->GetCurrentStage() );
}

void ACropActor::OnCropStageChanged( ECropGrowthStage NewStage )
{
    ApplyStageVisuals( NewStage );
}

void ACropActor::ApplyStageVisuals( ECropGrowthStage Stage )
{
    if ( !CropVisualData )
        return;

    const FCropStageVisual* Visual = CropVisualData->GetVisual( Stage );
    if ( !Visual )
        return;
    if ( Visual->Mesh )
    {
        MeshComponent->SetStaticMesh( Visual->Mesh );
    }
    if ( Visual->Material )
    {
        MeshComponent->SetMaterial( 0, Visual->Material );
    }
    if ( Visual->EnterStageFX )
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld(), Visual->EnterStageFX, GetActorLocation() );
    }
}
