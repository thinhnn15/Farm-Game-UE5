// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameInstance/FarmGameInstance.h"
#include "Public/Gameplay/Instance/GameplayInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UFarmGameInstance::Init()
{
    Super::Init();
}

void UFarmGameInstance::Shutdown()
{
    Super::Shutdown();
}

void UFarmGameInstance::RequestFromUIStartNewGame()
{
    UE_LOG( LogTemp, Warning, TEXT( "RequestFromUIStartNewGame" ) );
    UGameplayStatics::OpenLevel( this, FName( "L_Test_Crop" ) );
}

void UFarmGameInstance::RequestFromUIContinueGame()
{
    UE_LOG( LogTemp, Warning, TEXT( "FarmGameInstance::RequestFromUIContinueGame" ) );
}

void UFarmGameInstance::RequestFromUIExitGame( ULocalPlayer* RequestingPlayer )
{
    UE_LOG( LogTemp, Warning, TEXT( "FarmGameInstance::RequestFromUIExitGame" ) );

    if ( !RequestingPlayer )
        return;

    APlayerController* PC = RequestingPlayer->GetPlayerController( GetWorld() );
    if ( !PC )
        return;

    UKismetSystemLibrary::QuitGame( this, PC, EQuitPreference::Quit, false );
}
