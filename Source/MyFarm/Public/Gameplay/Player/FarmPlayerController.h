// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FarmPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCropTypeData;
class AFarmPlot;

UCLASS()
class MYFARM_API AFarmPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    void Debug_NextDay();
    void Debug_Harvest();
    void Debug_PlantCrop();
    void Debug_SelectSeed( FName SeedRowId );

protected:
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputMappingContext > DebugInputContext;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > NextDayAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > HarvestAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > PlantCropAction;

    // Debug Data
    UPROPERTY( EditDefaultsOnly, Category = "Debug" )
    FName DebugCropRowId;

private:
    AFarmPlot* GetHoveredPlot() const;
};
