// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Player/FarmPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Core/Data/FarmSeedSubsystem.h"
#include "Core/Inventory/FarmInventorySubsystem.h"
#include "Gameplay/Farm/FarmPlot.h"
#include "Gameplay/Tool/ToolBase.h"
#include "Gameplay/Tool/WateringTool.h"
#include "Public/Core/Time/FarmTimeSubsystem.h"
#include "Public/Gameplay/Crop/CropActor.h"

AFarmPlayerController::AFarmPlayerController()
{
}

void AFarmPlayerController::OnSeedSelected( FName SeedRowId )
{
    UE_LOG( LogTemp, Warning, TEXT( "[Debug] Selected Seed: %s" ), *SeedRowId.ToString() );
    if ( !PlayerInventory )
        return;

    // Store the selected seed into gameplay inventory
    PlayerInventory->SetSelectedSeed( SeedRowId );
}

void AFarmPlayerController::SetCurrentTool( UToolBase* NewTool )
{
    CurrentTool = NewTool;
}

UToolBase* AFarmPlayerController::GetCurrentTool() const
{
    return CurrentTool;
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
    EnhancedInputComponent->BindAction( PlantCropAction, ETriggerEvent::Started, this, &AFarmPlayerController::TryPlant );
    ensure( ToggleInventoryAction );
    EnhancedInputComponent->BindAction( ToggleInventoryAction, ETriggerEvent::Started, this, &AFarmPlayerController::Debug_ToggleInventory );
    ensure( UseWaterToolAction );
    EnhancedInputComponent->BindAction( UseWaterToolAction, ETriggerEvent::Started, this, &AFarmPlayerController::EquipWateringTool );
    ensure( UseToolAction );
    EnhancedInputComponent->BindAction( UseToolAction, ETriggerEvent::Started, this, &AFarmPlayerController::UseTool );
}

void AFarmPlayerController::BeginPlay()
{
    Super::BeginPlay();

    WateringTool = NewObject< UWateringTool >( this );
    HoeTool = NewObject< UHoeTool >( this );
    HarvestTool = NewObject< UHarvestTool >( this );

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    FInputModeGameAndUI InputMode;
    InputMode.SetHideCursorDuringCapture( false );
    SetInputMode( InputMode );
    UGameInstance* GI = GetGameInstance();
    if ( !GI )
        return;
    // Create the gameplay inventory for this player
    PlayerInventory = NewObject< UPlayerInventory >( this );

    UFarmInventorySubsystem* Inventory = GI->GetSubsystem< UFarmInventorySubsystem >();
    if ( !Inventory )
        return;
    Inventory->AddItem( "Carrot", 10 );
    Inventory->AddItem( "Wheat", 5 );
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

void AFarmPlayerController::TryPlant()
{
    if ( !PlayerInventory )
        return;

    if ( !PlayerInventory->HasSeed() )
        return;

    // Raycast -> FarmPlot
    AFarmPlot* Plot = GetHoveredPlot();
    if ( !Plot )
        return;

    // Get the selected crop row id from inventory
    const FName CropRowId = PlayerInventory->GetSelectedSeed();

    if ( Plot->PlantCrop( CropRowId ) )
    {
        PlayerInventory->ConsumeSeed();
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
        InputMode.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );
        InputMode.SetHideCursorDuringCapture( false );
        // Optional: focus UI
        InputMode.SetWidgetToFocus( InventoryWidget->TakeWidget() );
        SetInputMode( InputMode );
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

void AFarmPlayerController::UseTool()
{
    // TNN-TODO: Need to remove this logic to character?
    if ( !CurrentTool )
        return;

    FHitResult Hit;
    GetHitResultUnderCursor( ECC_Visibility, false, Hit );

    FToolUseContext Context;
    Context.InstigatorController = this;
    Context.InstigatorPawn = GetPawn();
    Context.TargetActor = Hit.GetActor();
    Context.HitResult = Hit;
    Context.WorldLocation = Hit.bBlockingHit ? Hit.Location : FVector::ZeroVector;
    Context.WorldNormal = Hit.bBlockingHit ? Hit.Normal : FVector::UpVector;
    Context.bIsPrimaryAction = true;

    if ( !CurrentTool->CanUse( Context ) )
        return;

    CurrentTool->Use( Context );
}

void AFarmPlayerController::EquipWateringTool()
{
    if ( !WateringTool )
        return;
    SetCurrentTool( WateringTool );
}

void AFarmPlayerController::EquipHoeTool()
{
    if ( !HoeTool )
        return;
    SetCurrentTool( HoeTool );
}

void AFarmPlayerController::EquipHarvestTool()
{
    if ( !HarvestTool )
        return;
    SetCurrentTool( HarvestTool );
}

AActor* AFarmPlayerController::GetHoveredActor() const
{
    FHitResult Hit;
    GetHitResultUnderCursor( ECC_Visibility, false, Hit );
    if ( !Hit.bBlockingHit )
        return nullptr;
    return Hit.GetActor();
}

AFarmPlot* AFarmPlayerController::GetHoveredPlot() const
{
    FHitResult Hit;
    GetHitResultUnderCursor( ECC_Visibility, false, Hit );
    if ( !Hit.bBlockingHit )
        return nullptr;

    return Cast< AFarmPlot >( Hit.GetActor() );
}
