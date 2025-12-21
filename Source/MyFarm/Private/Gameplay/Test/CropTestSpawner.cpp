// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Test/CropTestSpawner.h"
#include "Gameplay/Crop/CropActor.h"
#include "Gameplay/Crop/CropInstance.h"

void ACropTestSpawner::BeginPlay()
{
    Super::BeginPlay();

    if ( !TestCropType || !CropActorClass )
        return;

    // Create Crop Instance (logic)
    UCropInstance* CropInstance = NewObject< UCropInstance >( GetGameInstance() );
    CropInstance->Init( TestCropType );

    // Spawn Crop Actor (visual)
    ACropActor* CropActor = GetWorld()->SpawnActor< ACropActor >( CropActorClass, GetActorLocation(), FRotator::ZeroRotator );

    // Bind logic -> visual
    CropActor->BindCropInstance( CropInstance );
}
