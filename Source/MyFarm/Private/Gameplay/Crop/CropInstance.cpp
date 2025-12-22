// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Crop/CropInstance.h"
#include "Core/Time/FarmTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

bool UCropInstance::TryHarvest()
{
    if ( !CanHarvest() )
    {
        UE_LOG( LogTemp, Warning,
                TEXT("[CropInstance] %s cannot be harvested at stage %d"),
                *GetNameSafe(CropData),
                (int32)CurrentStage
        );
        return false;
    }

    Harvest();
    return true;
}

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

bool UCropInstance::Harvest()
{
    OnHarvested.Broadcast();
    UE_LOG( LogTemp, Log,
            TEXT("[CropInstance] %s harvested at day %d"),
            *GetNameSafe(CropData),
            DaysGrown
    );
    // Handle regrow
    if ( CropData->IsRegrowable() )
    {
        UE_LOG( LogTemp, Log,
                TEXT("[CropInstance] %s is regrowable, entering regrow phase"),
                *GetNameSafe(CropData)
        );
        EnterRegrow();
    }
    else
    {
        UE_LOG( LogTemp, Log,
                TEXT("[CropInstance] %s has no regrow, marking as Dead"),
                *GetNameSafe(CropData)
        );
        CurrentStage = ECropGrowthStage::Dead;
        OnStageChanged.Broadcast( CurrentStage );
    }
    return true;
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
