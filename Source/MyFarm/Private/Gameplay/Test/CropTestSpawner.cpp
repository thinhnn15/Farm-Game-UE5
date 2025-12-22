// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Test/CropTestSpawner.h"

#include "Gameplay/Crop/CropActor.h"
#include "Gameplay/Crop/CropInstance.h"

ACropTestSpawner::ACropTestSpawner()
{
    Root = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );
    SetRootComponent( Root );
    
    // Mesh
    MeshComponent = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "MeshComponent" ) );
    MeshComponent->SetupAttachment( Root );
    
    MeshComponent->SetMobility( EComponentMobility::Movable );
    MeshComponent->SetVisibility( true );
    MeshComponent->SetHiddenInGame( false );
}

void ACropTestSpawner::BeginPlay()
{
    Super::BeginPlay();

    if ( !TestCropType || !CropActorClass )
        return;

    // Create Crop Instance (logic)
    UCropInstance* CropInstance = NewObject< UCropInstance >( GetGameInstance() );
    CropInstance->Init( TestCropType );


    FVector SpawnLocation = GetActorLocation();
    SpawnLocation.Z += 100.f;

    FActorSpawnParameters Params;
    Params.Owner = this;
    // Spawn Crop Actor (visual)
    ACropActor* CropActor =
        GetWorld()->SpawnActor< ACropActor >(
            CropActorClass,
            SpawnLocation,
            FRotator::ZeroRotator,
            Params
        );
    // Bind logic -> visual
    CropActor->BindCropInstance( CropInstance );
}
