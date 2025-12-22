// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"
#include "Core/Time/FarmTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UCropInstance::Init( UCropTypeData* InCropTypeData )
{
    CropData = InCropTypeData;
    DaysGrown = 0;
    CurrentStage = ECropGrowthStage::Seed;
    InitializeInstance();
}

void UCropInstance::OnDayAdvanced( int32 NewDay )
{
    DaysGrown++;
    UpdateGrowthStage();
}

ECropGrowthStage UCropInstance::GetCurrentStage() const
{
    return CurrentStage;
}

UCropTypeData* UCropInstance::GetCropData() const
{
    return CropData;
}

bool UCropInstance::CanHarvest() const
{
    return CropData
        && CropData->CanHarvestAtStage( CurrentStage );
}

void UCropInstance::Harvest()
{
    if ( !CanHarvest() )
        return;

    OnHarvested.Broadcast();
    // Handle regrow
    if ( CropData->IsRegrowable() )
        EnterRegrow();
    else
    {
        CurrentStage = ECropGrowthStage::Dead;
        OnStageChanged.Broadcast( CurrentStage );
    }
}

void UCropInstance::UpdateGrowthStage()
{
    if ( !CropData )
        return;

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

void UCropInstance::EnterRegrow()
{
    // Roll back growth days so it regrows faster
    DaysGrown = FMath::Max( 0, CropData->GetTotalGrowthDays() - CropData->GetRegrowDays() );
    
    CurrentStage = ECropGrowthStage::Growing;
    OnStageChanged.Broadcast( CurrentStage );
}

void UCropInstance::OnInitialize()
{
    Super::OnInitialize();

    UGameInstance* GI = GetTypedOuter< UGameInstance >();
    if ( !GI )
        return;

    UFarmTimeSubsystem* TimeSubsystem = GI->GetSubsystem< UFarmTimeSubsystem >();
    if ( !TimeSubsystem )
        return;

    TimeSubsystem->RegisterDayListener( this );
}

void UCropInstance::OnDeinitialize()
{
    Super::OnDeinitialize();

    UGameInstance* GI = GetTypedOuter< UGameInstance >();
    if ( !GI )
        return;

    UFarmTimeSubsystem* TimeSubsystem = GI->GetSubsystem< UFarmTimeSubsystem >();
    if ( !TimeSubsystem )
        return;

    TimeSubsystem->UnregisterDayListener( this );
}
