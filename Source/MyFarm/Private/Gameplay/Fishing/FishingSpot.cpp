// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Fishing/FishingSpot.h"


AFishingSpot::AFishingSpot()
{
    PrimaryActorTick.bCanEverTick = true;
}

bool AFishingSpot::CanFish() const
{
    return true;
}

void AFishingSpot::StartFishing( APlayerController* PlayerController )
{
    if ( !CanFish() )
        return;

    SetFishingState( EFishingState::WaitingForBite );

    float BiteDelay = FMath::RandRange( 2.f, 5.f );
    GetWorld()->GetTimerManager().SetTimer( TimerHandle, this, &AFishingSpot::TriggerBite, BiteDelay, false );

    UE_LOG( LogTemp, Log, TEXT("Started fishing, waiting for bite in %.2f seconds"), BiteDelay );
}

void AFishingSpot::ResolveCatch( bool bCaughtFish )
{
    if ( !bCaughtFish )
    {
        SetFishingState( EFishingState::Failed );
        return;
    }
    
    SetFishingState( EFishingState::Success );
    const FFishTypeRow& Fish = AvailableFishTypes[FMath::RandHelper( AvailableFishTypes.Num() )];
    
    // TODO: Add fish to player inventory
}

void AFishingSpot::TriggerBite()
{
    SetFishingState( EFishingState::Bite );
    UE_LOG( LogTemp, Log, TEXT("A fish has bitten!") );
}

void AFishingSpot::SetFishingState( EFishingState NewState )
{
    if ( FishingState == NewState )
        return;

    FishingState = NewState;
    UE_LOG( LogTemp, Log, TEXT("Fishing state changed to %d"), static_cast<int32>(FishingState) );
}
