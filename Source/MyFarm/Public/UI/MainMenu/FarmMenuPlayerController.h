// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Gameplay/Player/FarmPlayerController.h"
#include "InputActionValue.h"
#include "FarmMenuPlayerController.generated.h"

class UFarmMainMenuWidget;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MYFARM_API AFarmMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UPROPERTY( EditDefaultsOnly, Category = "UI" )
    TSubclassOf< UFarmMainMenuWidget > MainMenuWidgetClass;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputMappingContext > MainMenuMappingContext;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > IAMenuMoveUp;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > IAMenuMoveDown;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > IAConfirmAction;

private:
    UPROPERTY()
    UFarmMainMenuWidget* MainMenuWidget;

    void HandleMenuMoveUp();
    void HandleMenuMoveDown();
    void HandleMenuMove( bool bMoveUp );
    void HandleMenuConfirm( const FInputActionValue& Value );
};
