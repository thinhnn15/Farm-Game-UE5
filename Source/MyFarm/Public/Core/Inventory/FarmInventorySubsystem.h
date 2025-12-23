// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Public/UI/Inventory/InventoryItemViewData.h"
#include "FarmInventorySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventoryChanged );

/**
 * Global inventory for the player (seeds, crops, items, etc.)
 */
UCLASS()
class MYFARM_API UFarmInventorySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Add items (stackable)
    UFUNCTION( BlueprintCallable, Category = "Inventory" )
    bool AddItem( FName ItemRowId, int32 Amount );

    // Remove item
    UFUNCTION( BlueprintCallable, Category = "Inventory" )
    bool RemoveItem( FName ItemRowId, int32 Amount );

    // Check item count
    UFUNCTION( BlueprintPure, Category = "Inventory" )
    int32 GetItemCount( FName ItemRowId ) const;

    // Check if has enough items
    UFUNCTION( BlueprintPure, Category = "Inventory" )
    bool HasItem( FName ItemRowId, int32 RequiredAmount = 1 ) const;

    UFUNCTION( BlueprintCallable, Category = "Inventory" )
    void GetAllItems( TArray< FInventoryItemViewData >& OutItems ) const;

    UFUNCTION( BlueprintCallable, Category = "Inventory" )
    const TMap< FName, int32 >& GetAllSeeds() const;

    // Debug helper
    UFUNCTION( BlueprintCallable, Category = "Inventory|Debug" )
    void Debug_AddItem( FName ItemRowId, int32 Amount );

public:
    UPROPERTY( BlueprintAssignable, Category = "Inventory" )
    FOnInventoryChanged OnInventoryChanged;

private:
    // ItemRowId -> Count
    UPROPERTY()
    TMap< FName, int32 > InventoryItems;
};
