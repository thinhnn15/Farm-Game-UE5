// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Gameplay/Tool/HarvestTool.h"
#include "Gameplay/Tool/HoeTool.h"
#include "Gameplay/Tool/WateringTool.h"
#include "Public/Gameplay/Inventory/PlayerInventory.h"
#include "UI/Inventory/SeedItemEntryWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "FarmPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCropTypeData;
class AFarmPlot;
class UToolBase;

UCLASS()
class MYFARM_API AFarmPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AFarmPlayerController();
    void OnSeedSelected( FName SeedRowId );
    // Sets the currently equipped tool
    void SetCurrentTool( UToolBase* NewTool );
    UToolBase* GetCurrentTool() const;

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    void Debug_NextDay();
    void Debug_Harvest();
    void TryPlant();
    void Debug_SelectSeed( FName SeedRowId );
    void Debug_ToggleInventory();
    void UseTool();
    void EquipWateringTool();
    void EquipHoeTool();
    void EquipHarvestTool();

    AActor* GetHoveredActor() const;

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

    // For debug, need to move this logic to inventory later
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > EquipHoeAction;

    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > EquipWateringCanAction;
    
    UPROPERTY( EditDefaultsOnly, Category = "Input" )
    TObjectPtr< UInputAction > EquipHarvestToolAction;

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

    // Tool instance
    UPROPERTY()
    TObjectPtr< UWateringTool > WateringTool;

    UPROPERTY()
    TObjectPtr< UHoeTool > HoeTool;

    UPROPERTY()
    TObjectPtr< UHarvestTool > HarvestTool;

private:
    AFarmPlot* GetHoveredPlot() const;

    UPROPERTY()
    TObjectPtr< UToolBase > CurrentTool;
};
