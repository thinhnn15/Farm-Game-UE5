// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Player/FarmPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Public/Core/Time/FarmTimeSubsystem.h"
#include "Public/Gameplay/Crop/CropActor.h"

void AFarmPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if ( !IsLocalController() )
        return;

    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if ( !LocalPlayer )
        return;

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem >( LocalPlayer );
    if ( !Subsystem )
        return;
    ensure( DebugInputContext );
    Subsystem->AddMappingContext( DebugInputContext, 0 );

    // Bind Input Actions
    UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent >( InputComponent );
    if ( !EnhancedInputComponent )
        return;

    ensure( NextDayAction );
    EnhancedInputComponent->BindAction( NextDayAction, ETriggerEvent::Started, this, &AFarmPlayerController::Debug_NextDay );
    ensure( HarvestAction );
    EnhancedInputComponent->BindAction( HarvestAction, ETriggerEvent::Started, this, &AFarmPlayerController::Debug_Harvest );
}

void AFarmPlayerController::Debug_NextDay()
{
    UGameInstance* GameInstance = GetGameInstance();
    if ( !GameInstance )
        return;

    UFarmTimeSubsystem* TimeSubsystem = GameInstance->GetSubsystem< UFarmTimeSubsystem >();
    if ( !TimeSubsystem )
        return;

    TimeSubsystem->AdvanceDay();
}

void AFarmPlayerController::Debug_Harvest()
{
    UWorld* World = GetWorld();
    if ( !World )
        return;

    // Debug: find the first CropActor in level
    for ( TActorIterator< ACropActor > It( World ); It; ++It )
    {
        ACropActor* CropActor = *It;
        if ( CropActor )
        {
            UE_LOG( LogTemp, Log, TEXT( "[Debug] TryHarvest()" ) );
            CropActor->TryHarvest();
            return;;
        }
    }
    UE_LOG( LogTemp, Warning, TEXT( "[Debug] No CropActor found in level" ) );
}
