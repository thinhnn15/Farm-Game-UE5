// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Inventory/FarmInventorySubsystem.h"
#include "InventoryWidget.generated.h"

class UVerticalBox;
class UTextBlock;
class USeedItemEntryWidget;
class UFarmInventorySubsystem;

UCLASS()
class MYFARM_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Called to rebuild inventory UI
    UFUNCTION( BlueprintCallable )
    void RefreshInventory();

    // Get selected seed for planting
    FName GetSelectedSeed() const;

protected:
    virtual void NativeConstruct() override;

    void HandleSeedSelected( FName SeedRowId );

protected:
    // BindWidget
    UPROPERTY( meta = ( BindWidget ) )
    TObjectPtr< UVerticalBox > VB_InventoryList;

    UPROPERTY( meta = ( BindWidget ) )
    TObjectPtr< UTextBlock > Txt_SelectedSeed;

    // Config
    UPROPERTY( EditDefaultsOnly, Category="Inventory|UI" )
    TSubclassOf< USeedItemEntryWidget > SeedItemEntryWidgetClass;

private:
    // Runtime cache
    UPROPERTY()
    TObjectPtr< UFarmInventorySubsystem > InventorySubsystem;

    TMap< FName, TObjectPtr< USeedItemEntryWidget > > SeedItemWidgets;

    FName SelectedSeedRowId = NAME_None;
};
