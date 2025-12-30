// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FarmCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UEhancedInputComponent;
class UInputAction;
class USphereComponent;
class AFarmPlot;

UCLASS()
class MYFARM_API AFarmCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFarmCharacter();

    AFarmPlot* GetCurrentInteractablePlot() const;

    virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
    void RequestUseTool();

protected:
    virtual void BeginPlay() override;

    // Camera boom positioning the camera behind the character
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Camera" )
    TObjectPtr< USpringArmComponent > CameraBoom;

    // Follow camera
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Camera" )
    TObjectPtr< UCameraComponent > FollowCamera;

    // Input actions
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > MoveAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > UseToolAction;

    UFUNCTION()
    void OnInteractSphereBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                       bool bFromSweep, const FHitResult& SweepResult );

    UFUNCTION()
    void OnInteractSphereEndOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

protected:
    // Interaction detection
    UPROPERTY( VisibleAnywhere, Category = "Interaction" )
    TObjectPtr< USphereComponent > InteractSphere;

    // Currently overlapped farm plot
    UPROPERTY()
    TObjectPtr< AFarmPlot > CurrentInteractablePlot;

protected:
    void HandleMove( const FInputActionValue& Value );
    void HandleUseTool( const FInputActionValue& Value );
};

static bool IsActorInCameraView(
    APlayerController* PC,
    const AActor* Actor
)
{
    if ( !PC || !Actor )
        return false;

    FVector2D ScreenPos;
    if ( !PC->ProjectWorldLocationToScreen(
        Actor->GetActorLocation(),
        ScreenPos,
        true ) )
    {
        return false;
    }

    int32 SizeX, SizeY;
    PC->GetViewportSize( SizeX, SizeY );

    return ScreenPos.X >= 0 && ScreenPos.X <= SizeX &&
        ScreenPos.Y >= 0 && ScreenPos.Y <= SizeY;
}
