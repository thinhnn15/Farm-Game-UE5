// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFishingState.h"
#include "FishTypeData.h"
#include "GameFramework/Actor.h"
#include "FishingSpot.generated.h"

UCLASS()
class MYFARM_API AFishingSpot : public AActor
{
    GENERATED_BODY()

public:
    AFishingSpot();

    bool CanFish() const;
    void StartFishing( APlayerController* PlayerController );
    void ResolveCatch(bool bCaughtFish);

protected:
    UPROPERTY()
    EFishingState FishingState = EFishingState::Idle;

    UPROPERTY( EditAnywhere )
    TArray< FFishTypeRow > AvailableFishTypes;
    
    FTimerHandle TimerHandle;
    
    void TriggerBite();
    void SetFishingState( EFishingState NewState );
};
