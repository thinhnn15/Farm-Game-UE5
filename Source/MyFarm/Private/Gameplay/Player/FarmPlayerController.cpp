// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Player/FarmPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Gameplay/Farm/FarmPlot.h"
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
    ensure( PlantCropAction );
    EnhancedInputComponent->BindAction( PlantCropAction, ETriggerEvent::Started, this, &AFarmPlayerController::Debug_PlantCrop );
}

void AFarmPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    FInputModeGameAndUI InputMode;
    InputMode.SetHideCursorDuringCapture( false );
    SetInputMode( InputMode );
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
    AFarmPlot* Plot = GetHoveredPlot();
    if ( !Plot )
    {
        UE_LOG( LogTemp, Log, TEXT( "[Debug] No Plot found" ) );
        return;
    }
    
    Plot->TryHarvest();
}

void AFarmPlayerController::Debug_PlantCrop()
{
    AFarmPlot* Plot = GetHoveredPlot();
    if ( !Plot )
    {
        UE_LOG( LogTemp, Log, TEXT( "[Debug] No Plot found" ) );
        return;
    }
    
    Plot->PlantCrop( DebugCropRowId );
}

AFarmPlot* AFarmPlayerController::GetHoveredPlot() const
{
    FHitResult Hit;
    GetHitResultUnderCursor( ECC_Visibility, false, Hit );
    if ( !Hit.bBlockingHit )
        return nullptr;

    return Cast< AFarmPlot >( Hit.GetActor() );
}
