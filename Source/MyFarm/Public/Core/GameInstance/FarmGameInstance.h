// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FarmGameInstance.generated.h"

class UGameplayInstanceBase;

UCLASS()
class MYFARM_API UFarmGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;
    virtual void Shutdown() override;

    // API for UI
    UFUNCTION( Blueprintable )
    void RequestFromUIStartNewGame();

    UFUNCTION( BlueprintCallable )
    void RequestFromUIContinueGame();

    UFUNCTION( BlueprintCallable )
    void RequestFromUIExitGame( ULocalPlayer* RequestingPlayer );
};
