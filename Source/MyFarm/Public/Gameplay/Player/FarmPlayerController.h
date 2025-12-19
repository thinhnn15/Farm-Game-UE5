// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FarmPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MYFARM_API AFarmPlayerController : public APlayerController
{
    GENERATED_BODY()
protected:
    virtual void SetupInputComponent() override;
    
    void Debug_NextDay();
    
protected:
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    UInputMappingContext* DebugInputContext;
    
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    UInputAction* NextDayAction;
};
