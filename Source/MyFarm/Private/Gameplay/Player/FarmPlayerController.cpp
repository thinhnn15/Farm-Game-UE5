// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Player/FarmPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Core/Data/FarmSeedSubsystem.h"
#include "Core/Inventory/FarmInventorySubsystem.h"
#include "Gameplay/Farm/FarmPlot.h"
#include "Public/Core/Time/FarmTimeSubsystem.h"
#include "Public/Gameplay/Crop/CropActor.h"

AFarmPlayerController::AFarmPlayerController()
{
}

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
    ensure( ToggleInventoryAction );
    EnhancedInputComponent->BindAction( ToggleInventoryAction, ETriggerEvent::Started, this, &AFarmPlayerController::Debug_ToggleInventory );
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
    UGameInstance* GI = GetGameInstance();
    if ( !GI )
        return;
    UFarmInventorySubsystem* Inventory = GI->GetSubsystem< UFarmInventorySubsystem >();
    if ( !Inventory )
        return;
    Inventory->AddItem( "Seed_Carrot", 10 );
    Inventory->AddItem( "Seed_Wheat", 5 );
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
    UGameInstance* GI = GetGameInstance();
    if ( !GI )
        return;

    UFarmInventorySubsystem* Inventory = GI->GetSubsystem< UFarmInventorySubsystem >();
    if ( !Inventory )
        return;

    if ( !Inventory->HasItem( "Seed_Carrot", 1 ) )
    {
        UE_LOG( LogTemp, Warning, TEXT("[Debug] Not enough seeds of Seed_Carrot to plant.") );
        return;
    }

    // Raycast -> FarmPlot
    AFarmPlot* Plot = GetHoveredPlot();
    if ( !Plot )
        return;

    if ( Plot->PlantCrop( "Carrot" ) )
    {
        Inventory->RemoveItem( "Seed_Carrot", 1 );
    }
}

void AFarmPlayerController::Debug_SelectSeed( FName SeedRowId )
{
    UFarmSeedSubsystem* SeedSubsystem = GetGameInstance()->GetSubsystem< UFarmSeedSubsystem >();
    if ( !SeedSubsystem )
        return;

    const FSeedItemRow* SeedData = SeedSubsystem->GetSeedData( SeedRowId );
    if ( !SeedData )
    {
        UE_LOG( LogTemp, Warning, TEXT( "[Debug] SeedRowId %s not found" ), *SeedRowId.ToString() );
        return;
    }
}

void AFarmPlayerController::Debug_ToggleInventory()
{
    if ( !InventoryWidget )
    {
        if ( !InventoryWidgetClass )
            return;

        InventoryWidget = CreateWidget< UInventoryWidget >( this, InventoryWidgetClass );
        if ( !InventoryWidget )
            return;

        InventoryWidget->AddToViewport();

        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);
        // Optional: focus UI
        InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
        SetInputMode(InputMode);
        // Show mouse
        bShowMouseCursor = true;

        UE_LOG( LogTemp, Log, TEXT( "[Debug] Inventory Click" ) );
        return;
    }
    InventoryWidget->RemoveFromParent();
    InventoryWidget = nullptr;

    // Hide mouse
    bShowMouseCursor = false;
    SetInputMode( FInputModeGameOnly() );

    UE_LOG( LogTemp, Log, TEXT( "[Debug] Inventory Click" ) );
}

AFarmPlot* AFarmPlayerController::GetHoveredPlot() const
{
    FHitResult Hit;
    GetHitResultUnderCursor( ECC_Visibility, false, Hit );
    if ( !Hit.bBlockingHit )
        return nullptr;

    return Cast< AFarmPlot >( Hit.GetActor() );
}
