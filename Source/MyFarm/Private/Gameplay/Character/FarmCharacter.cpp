// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Character/FarmCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Gameplay/Player/FarmPlayerController.h"
#include "Gameplay/Tool/ToolUseContext.h"
#include "Gameplay/Tool/ToolBase.h"

AFarmCharacter::AFarmCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Character rotates based on movement direction
    bUseControllerRotationYaw = false;

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    if ( MoveComp )
    {
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator( 0.f, 540.f, 0.f );
        MoveComp->MaxWalkSpeed = 400.f;
    }

    // Camera setup
    CameraBoom = CreateDefaultSubobject< USpringArmComponent >( TEXT( "CameraBoom" ) );
    CameraBoom->SetupAttachment( RootComponent );
    CameraBoom->TargetArmLength = 350.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject< UCameraComponent >( TEXT( "FollowCamera" ) );
    FollowCamera->SetupAttachment( CameraBoom, USpringArmComponent::SocketName );
    FollowCamera->bUsePawnControlRotation = false;
}

void AFarmCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AFarmCharacter::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
    Super::SetupPlayerInputComponent( PlayerInputComponent );

    UEnhancedInputComponent* EnhancedInput = Cast< UEnhancedInputComponent >( PlayerInputComponent );
    if ( !EnhancedInput )
        return;

    if ( MoveAction )
    {
        EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AFarmCharacter::HandleMove );
    }

    if ( UseToolAction )
    {
        EnhancedInput->BindAction( UseToolAction, ETriggerEvent::Started, this, &AFarmCharacter::HandleUseTool );
    }
}

void AFarmCharacter::RequestUseTool()
{
    AFarmPlayerController* FarmPC = Cast< AFarmPlayerController >( GetController() );
    if ( !FarmPC )
        return;
    
    UToolBase* Tool = FarmPC->GetCurrentTool();
    if ( !Tool )
        return;
    
    FToolUseContext Context;
    Context.InstigatorController = FarmPC;
    Context.InstigatorPawn = this;
    
    Tool->Use(Context);
}

void AFarmCharacter::HandleMove( const FInputActionValue& Value )
{
    const FVector2D MoveValue = Value.Get< FVector2D >();
    if ( !Controller )
        return;

    if ( MoveValue.IsNearlyZero() )
        return;

    const FRotator YawRotation( 0.f, Controller->GetControlRotation().Yaw, 0.f );
    const FVector Forward = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
    const FVector Right = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
    AddMovementInput( Forward, MoveValue.Y );
    AddMovementInput( Right, MoveValue.X );
}

void AFarmCharacter::HandleUseTool( const FInputActionValue& Value )
{
    UE_LOG( LogTemp, Warning, TEXT("%s"), TEXT("Use Tool") );
    RequestUseTool();
}
