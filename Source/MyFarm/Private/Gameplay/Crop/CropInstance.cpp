// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"
#include "Core/Time/FarmTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UCropInstance::Init( UCropTypeData* InCropTypeData )
{
    CropData = InCropTypeData;
    DaysGrown = 0;
    CurrentStage = ECropGrowthStage::Seed;
}

void UCropInstance::OnDayAdvanced( int32 NewDay )
{
    if ( !CropData )
        return;

    DaysGrown++;
    // Determine stage from data
    const ECropGrowthStage NewStage = CropData->GetStageForDay( DaysGrown );

    if ( NewStage == CurrentStage )
        return;

    CurrentStage = NewStage;
    UE_LOG( LogTemp, Log,
            TEXT("[CropInstance] %s advanced to stage %d at day %d"),
            *GetNameSafe(CropData),
            (int32)CurrentStage,
            DaysGrown
    );
    OnStageChanged.Broadcast( CurrentStage );
}

ECropGrowthStage UCropInstance::GetCurrentStage() const
{
    return CurrentStage;
}

UCropTypeData* UCropInstance::GetCropData() const
{
    return CropData;
}

void UCropInstance::OnInitialize()
{
    Super::OnInitialize();

    UWorld* World = GetWorld();
    if ( !World )
        return;

    UGameInstance* GI = World->GetGameInstance();
    if ( !GI )
        return;

    UFarmTimeSubsystem* FarmTimeSubsystem = GI->GetSubsystem< UFarmTimeSubsystem >();
    if ( !FarmTimeSubsystem )
        return;

    FarmTimeSubsystem->RegisterDayListener( this );
}

void UCropInstance::OnDeinitialize()
{
    Super::OnDeinitialize();
    UWorld* World = GetWorld();
    if ( !World )
        return;

    UGameInstance* GI = World->GetGameInstance();
    if ( !GI )
        return;
    
    UFarmTimeSubsystem* FarmTimeSubsystem = GI->GetSubsystem< UFarmTimeSubsystem >();
    if ( !FarmTimeSubsystem )
        return;
    
    FarmTimeSubsystem->UnregisterDayListener( this );
}
