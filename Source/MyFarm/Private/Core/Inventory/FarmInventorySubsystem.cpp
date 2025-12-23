// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/FarmInventorySubsystem.h"

bool UFarmInventorySubsystem::AddItem( FName ItemRowId, int32 Amount )
{
    if ( ItemRowId.IsNone() || Amount <= 0 )
    {
        UE_LOG( LogTemp, Warning, TEXT("[FarmInventorySubsystem] Invalid item addition request: %s x%d"), *ItemRowId.ToString(), Amount );
        return false;
    }
    InventoryItems.FindOrAdd( ItemRowId ) += Amount;

    UE_LOG( LogTemp, Log, TEXT("[FarmInventorySubsystem] Added item: %s x%d"), *ItemRowId.ToString(), Amount );

    OnInventoryChanged.Broadcast();
    return true;
}

bool UFarmInventorySubsystem::RemoveItem( FName ItemRowId, int32 Amount )
{
    if ( !HasItem( ItemRowId, Amount ) )
        return false;

    int32& Count = InventoryItems[ ItemRowId ];
    Count -= Amount;
    if ( Count <= 0 )
    {
        InventoryItems.Remove( ItemRowId );
    }

    UE_LOG( LogTemp, Log, TEXT("[FarmInventorySubsystem] Removed item: %s x%d"), *ItemRowId.ToString(), Amount );
    OnInventoryChanged.Broadcast();
    return true;
}

int32 UFarmInventorySubsystem::GetItemCount( FName ItemRowId ) const
{
    const int32* Count = InventoryItems.Find( ItemRowId );
    return Count ? *Count : 0;
}

bool UFarmInventorySubsystem::HasItem( FName ItemRowId, int32 RequiredAmount ) const
{
    return GetItemCount( ItemRowId ) >= RequiredAmount;
}

void UFarmInventorySubsystem::GetAllItems( TArray< FInventoryItemViewData >& OutItems ) const
{
    OutItems.Reset();
    for ( const auto& Pair : InventoryItems )
    {
        FInventoryItemViewData Item;
        Item.ItemRowId = Pair.Key;
        Item.Quantity = Pair.Value;
        OutItems.Add( Item );
    }
}

const TMap< FName, int32 >& UFarmInventorySubsystem::GetAllSeeds() const
{
    return InventoryItems;
}

void UFarmInventorySubsystem::Debug_AddItem( FName ItemRowId, int32 Amount )
{
    AddItem( ItemRowId, Amount );
}
