// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"

#include "Core/Data/FarmCropDataSubsystem.h"
#include "Core/Time/FarmTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

bool UCropInstance::TryHarvest()
{
    if ( !CanHarvest() )
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("[CropInstance] Cannot harvest crop [%s] at stage %d"),
            *CropRowId.ToString(),
            (int32)CurrentStage
        );
        return false;
    }

    Harvest();
    return true;
}

void UCropInstance::Init( FName InCropRowId )
{
    CropRowId = InCropRowId;

    UGameInstance* GI = GetTypedOuter< UGameInstance >();
    if ( !GI )
    {
        UE_LOG( LogTemp, Error,
                TEXT("[CropInstance] Failed to get GameInstance for CropInstance initialization.")
        );
        return;
    }

    UFarmCropDataSubsystem* CropDataSubsystem = GI->GetSubsystem< UFarmCropDataSubsystem >();
    if ( !CropDataSubsystem )
    {
        UE_LOG( LogTemp, Error,
                TEXT("[CropInstance] Failed to get FarmCropDataSubsystem for CropInstance initialization.")
        );
    }
    CropData = CropDataSubsystem->GetCropData( CropRowId );
    if ( !CropData )
    {
        UE_LOG( LogTemp, Error,
                TEXT("[CropInstance] Failed to find CropTypeData for RowId: %s"),
                *CropRowId.ToString()
        );
        return;
    }

    DaysGrown = 0;
    CurrentStage = ECropGrowthStage::Seed;
    InitializeInstance();
}

void UCropInstance::OnDayAdvanced( int32 NewDay )
{
    if ( !IsAlive() )
        return;

    DaysGrown++;
    UpdateGrowthStage();
}

ECropGrowthStage UCropInstance::GetCurrentStage() const
{
    return CurrentStage;
}

const FCropTypeRow* UCropInstance::GetCropData() const
{
    return CropData;
}

bool UCropInstance::IsAlive() const
{
    return CurrentStage != ECropGrowthStage::Dead;
}

bool UCropInstance::CanHarvest() const
{
    if ( !CropData )
        return false;

    return CurrentStage == ECropGrowthStage::Harvestable;
}

bool UCropInstance::Harvest()
{
    OnHarvested.Broadcast();
    UE_LOG(
        LogTemp,
        Log,
        TEXT("[CropInstance] Harvested crop [%s] at day %d"),
        *CropRowId.ToString(),
        DaysGrown
    );
    // Handle regrow
    if ( CropData->bRegrowable )
    {
        EnterRegrow();
    }
    else
    {
        CurrentStage = ECropGrowthStage::Dead;
        OnStageChanged.Broadcast( CurrentStage );
    }
    return true;
}

void UCropInstance::UpdateGrowthStage()
{
    if ( !CropData )
        return;

    ECropGrowthStage NewStage = CurrentStage;
    // Determine stage by threshold
    for ( const auto& Pair : CropData->GrowthStages )
    {
        if ( DaysGrown >= Pair.Key )
        {
            NewStage = Pair.Value;
        }
    }

    if ( NewStage == CurrentStage )
        return;

    CurrentStage = NewStage;
    UE_LOG(
        LogTemp,
        Log,
        TEXT("[CropInstance] Crop [%s] entered stage %d (Day %d)"),
        *CropRowId.ToString(),
        (int32)CurrentStage,
        DaysGrown
    );
    OnStageChanged.Broadcast( CurrentStage );
}

void UCropInstance::EnterRegrow()
{
    // Roll back growth days so it regrows faster
    DaysGrown = FMath::Max( 0, CropData->TotalGrowthDays - CropData->RegrowDays );

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
