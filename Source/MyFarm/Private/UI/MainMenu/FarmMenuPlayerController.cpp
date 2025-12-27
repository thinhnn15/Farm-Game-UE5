// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/FarmMenuPlayerController.h"
#include "UI/MainMenu/FarmMainMenuWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

void AFarmMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    MainMenuWidget = CreateWidget< UFarmMainMenuWidget >( this, MainMenuWidgetClass );

    if ( MainMenuWidget )
        MainMenuWidget->AddToViewport();

    FInputModeGameAndUI InputMode;
    InputMode.SetHideCursorDuringCapture( true );
    InputMode.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );

    SetInputMode( InputMode );
    bShowMouseCursor = false;

    // Add mapping context
    ULocalPlayer* LocalPlayer = GetLocalPlayer();
    if ( !LocalPlayer )
        return;
    UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem< UEnhancedInputLocalPlayerSubsystem >();
    if ( !Subsystem )
        return;

    Subsystem->AddMappingContext( MainMenuMappingContext, 0 );
}

void AFarmMenuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast< UEnhancedInputComponent >( InputComponent );
    if ( !EnhancedInput )
        return;

    EnhancedInput->BindAction( IAMenuMoveUp, ETriggerEvent::Started, this, &AFarmMenuPlayerController::HandleMenuMoveUp );
    EnhancedInput->BindAction( IAMenuMoveDown, ETriggerEvent::Started, this, &AFarmMenuPlayerController::HandleMenuMoveDown );
    EnhancedInput->BindAction( IAConfirmAction, ETriggerEvent::Started, this, &AFarmMenuPlayerController::HandleMenuConfirm );
}

void AFarmMenuPlayerController::HandleMenuMoveUp()
{
    HandleMenuMove( true );
}

void AFarmMenuPlayerController::HandleMenuMoveDown()
{
    HandleMenuMove( false );
}

void AFarmMenuPlayerController::HandleMenuMove( bool bMoveUp )
{
    if ( !MainMenuWidget )
        return;
    const int32 Direction = bMoveUp ? -1 : 1;
    MainMenuWidget->MoveSelection( Direction );
}

void AFarmMenuPlayerController::HandleMenuConfirm( const FInputActionValue& Value )
{
    if ( !MainMenuWidget )
        return;

    if ( Value.Get< bool >() )
        MainMenuWidget->ConfirmSelection();
}
