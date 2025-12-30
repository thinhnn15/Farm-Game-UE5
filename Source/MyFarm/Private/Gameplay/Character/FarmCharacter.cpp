// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Character/FarmCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Gameplay/Player/FarmPlayerController.h"
#include "Gameplay/Tool/ToolUseContext.h"
#include "Gameplay/Tool/ToolBase.h"
#include "Components/SphereComponent.h"
#include "Gameplay/Farm/FarmPlot.h"

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

    GetCharacterMovement()->MaxAcceleration = 2048.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;

    InteractSphere = CreateDefaultSubobject< USphereComponent >( TEXT( "InteractSphere" ) );
    InteractSphere->SetupAttachment( RootComponent );
    InteractSphere->SetSphereRadius( 200.f );

    InteractSphere->SetGenerateOverlapEvents( true );
    InteractSphere->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    InteractSphere->SetCollisionResponseToAllChannels( ECR_Ignore );
    InteractSphere->SetCollisionResponseToChannel( ECC_WorldDynamic, ECR_Overlap );
    InteractSphere->SetCollisionResponseToChannel( ECC_WorldStatic, ECR_Overlap );
}

AFarmPlot* AFarmCharacter::GetCurrentInteractablePlot() const
{
    return CurrentInteractablePlot;
}

void AFarmCharacter::BeginPlay()
{
    Super::BeginPlay();

    InteractSphere->OnComponentBeginOverlap.AddDynamic( this, &AFarmCharacter::OnInteractSphereBeginOverlap );
    InteractSphere->OnComponentEndOverlap.AddDynamic( this, &AFarmCharacter::OnInteractSphereEndOverlap );
}

void AFarmCharacter::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
    Super::SetupPlayerInputComponent( PlayerInputComponent );

    UEnhancedInputComponent* EnhancedInput = Cast< UEnhancedInputComponent >( PlayerInputComponent );
    if ( !EnhancedInput )
        return;

    if ( !MoveAction || !UseToolAction )
        return;
    EnhancedInput->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AFarmCharacter::HandleMove );
    EnhancedInput->BindAction( UseToolAction, ETriggerEvent::Started, this, &AFarmCharacter::HandleUseTool );
}

void AFarmCharacter::RequestUseTool()
{
    AFarmPlayerController* FarmPC = Cast< AFarmPlayerController >( GetController() );
    if ( !FarmPC )
        return;

    UToolBase* Tool = FarmPC->GetCurrentTool();
    if ( !Tool )
        return;
    // if ( !Tool )
    // {
    //     // TNN-TODO: For debug only
    //     UHoeTool* HoeTool = NewObject< UHoeTool >( this );
    //     FarmPC->SetCurrentTool( HoeTool );
    //     Tool = HoeTool;
    // }

    if ( !CurrentInteractablePlot )
        return;

    if ( !IsActorInCameraView( FarmPC, CurrentInteractablePlot ) )
        return;

    FToolUseContext Context;
    Context.InstigatorController = FarmPC;
    Context.InstigatorPawn = this;
    Context.TargetActor = CurrentInteractablePlot;
    Context.WorldLocation = CurrentInteractablePlot->GetActorLocation();

    Tool->Use( Context );
}

void AFarmCharacter::OnInteractSphereBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep
                                                   , const FHitResult& SweepResult )
{
    UE_LOG( LogTemp, Error, TEXT("SPHERE OVERLAP TRIGGERED WITH %s"), *OtherActor->GetName() );
    AFarmPlot* Plot = Cast< AFarmPlot >( OtherActor );
    if ( !Plot )
        return;

    CurrentInteractablePlot = Plot;
}

void AFarmCharacter::OnInteractSphereEndOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
    if ( OtherActor == CurrentInteractablePlot )
    {
        CurrentInteractablePlot = nullptr;
    }
}

void AFarmCharacter::HandleMove( const FInputActionValue& Value )
{
    FVector2D MoveValue = Value.Get< FVector2D >();
    if ( !Controller )
        return;

    if ( MoveValue.IsNearlyZero() )
        return;

    MoveValue = MoveValue.GetSafeNormal();

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
