// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Gameplay/Inventory/PlayerInventory.h"
#include "UI/Inventory/SeedItemEntryWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "FarmPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCropTypeData;
class AFarmPlot;

UCLASS()
class MYFARM_API AFarmPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AFarmPlayerController();

    void OnSeedSelected( FName SeedRowId );

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    void Debug_NextDay();
    void Debug_Harvest();
    void Debug_PlantCrop();
    void Debug_SelectSeed( FName SeedRowId );
    void Debug_ToggleInventory();

protected:
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputMappingContext > DebugInputContext;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > NextDayAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > HarvestAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > PlantCropAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > ToggleInventoryAction;

    UPROPERTY()
    TObjectPtr< UPlayerInventory > PlayerInventory;

    // Debug Data
    UPROPERTY( EditDefaultsOnly, Category = "Debug" )
    FName DebugCropRowId;

    UPROPERTY( EditDefaultsOnly, Category = "Debug" )
    FName SelectedSeedRowId;

    UPROPERTY()
    TObjectPtr< UInventoryWidget > InventoryWidget;

    UPROPERTY( EditDefaultsOnly, Category="UI" )
    TSubclassOf< UInventoryWidget > InventoryWidgetClass;

private:
    AFarmPlot* GetHoveredPlot() const;
};
