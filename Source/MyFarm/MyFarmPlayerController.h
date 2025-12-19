// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "MyFarmPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UPathFollowingComponent;

DECLARE_LOG_CATEGORY_EXTERN( LogTemplateCharacter, Log, All );

UCLASS( abstract )
class AMyFarmPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    UPROPERTY( VisibleDefaultsOnly, Category = AI )
    TObjectPtr< UPathFollowingComponent > PathFollowingComponent;

    UPROPERTY( EditAnywhere, Category="Input" )
    float ShortPressThreshold;

    UPROPERTY( EditAnywhere, Category="Input" )
    TObjectPtr< UNiagaraSystem > FXCursor;

    UPROPERTY( EditAnywhere, Category="Input" )
    TObjectPtr< UInputMappingContext > DefaultMappingContext;

    UPROPERTY( EditAnywhere, Category="Input" )
    TObjectPtr< UInputAction > SetDestinationClickAction;

    UPROPERTY( EditAnywhere, Category="Input" )
    TObjectPtr< UInputAction > SetDestinationTouchAction;

    /** True if the controlled character should navigate to the mouse cursor. */
    uint32 bMoveToMouseCursor : 1;

    /** Set to true if we're using touch input */
    uint32 bIsTouch : 1;

    /** Saved location of the character movement destination */
    FVector CachedDestination;

    /** Time that the click input has been pressed */
    float FollowTime = 0.0f;

public:
    AMyFarmPlayerController();

protected:
    virtual void SetupInputComponent() override;

    /** Input handlers */
    void OnInputStarted();
    void OnSetDestinationTriggered();
    void OnSetDestinationReleased();
    void OnTouchTriggered();
    void OnTouchReleased();

    /** Helper function to get the move destination */
    void UpdateCachedDestination();
};
