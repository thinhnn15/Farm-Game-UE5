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

    EnhancedInput->BindAction( IAMenuMoveAction, ETriggerEvent::Triggered, this, &AFarmMenuPlayerController::HandleMenuMove );
    EnhancedInput->BindAction( IAConfirmAction, ETriggerEvent::Started, this, &AFarmMenuPlayerController::HandleMenuConfirm );
}

void AFarmMenuPlayerController::HandleMenuMove( const FInputActionValue& Value )
{
    if ( !MainMenuWidget )
        return;

    const float AxisValue = Value.Get< float >();
    if ( FMath::Abs( AxisValue ) < KINDA_SMALL_NUMBER )
        return;

    const int32 Direction = AxisValue > 0.f ? 1 : 1;
    MainMenuWidget->MoveSelection( Direction );
}

void AFarmMenuPlayerController::HandleMenuConfirm( const FInputActionValue& Value )
{
    if ( !MainMenuWidget )
        return;

    if ( Value.Get< bool >() )
        MainMenuWidget->ConfirmSelection();
}
