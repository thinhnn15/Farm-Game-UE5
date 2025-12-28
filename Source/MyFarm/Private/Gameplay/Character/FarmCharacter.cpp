// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Character/FarmCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AFarmCharacter::AFarmCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Character Rotation
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
}
