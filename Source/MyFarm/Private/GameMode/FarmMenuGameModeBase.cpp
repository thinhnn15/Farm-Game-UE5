// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FarmMenuGameModeBase.h"

#include "UI/MainMenu/FarmMenuPlayerController.h"

AFarmMenuGameModeBase::AFarmMenuGameModeBase()
{
    DefaultPawnClass = nullptr;
    
    PlayerControllerClass = AFarmMenuPlayerController::StaticClass();
    
    HUDClass = nullptr;
    GameStateClass = nullptr;
    PlayerStateClass = nullptr;
}
