// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "Gameplay/Inventory/InventoryComponent.h"
//
// int32 UInventoryComponent::GetItemCount( FName ItemRowId ) const
// {
//     for ( const auto& Stack : Items )
//     {
//         if ( Stack.ItemRowId == ItemRowId )
//             return Stack.Count;
//     }
//     return 0;
// }
//
// bool UInventoryComponent::AddItem( FName ItemRowId, int32 Count )
// {
//     if ( ItemRowId == NAME_None || Count <= 0 )
//         return false;
//
//     for ( auto& Stack : Items )
//     {
//         if ( Stack.ItemRowId == ItemRowId )
//         {
//             Stack.Count += Count;
//             OnInventoryChanged.Broadcast();
//             return true;
//         }
//     }
//     Items.Add( { ItemRowId, Count } );
//     OnInventoryChanged.Broadcast();
//     return true;
// }
//
// bool UInventoryComponent::RemoveItem( FName ItemRowId, int32 Count )
// {
//     for (int32 i = 0; i < Items.Num(); ++i)
//     {
//         if (Items[i].ItemRowId == ItemRowId)
//         {
//             if (Items[i].Count < Count)
//                 return false;
//
//             Items[i].Count -= Count;
//             if (Items[i].Count <= 0)
//                 Items.RemoveAt(i);
//
//             OnInventoryChanged.Broadcast();
//             return true;
//         }
//     }
//     return false;
// }
//
// bool UInventoryComponent::ConsumeItem( FName ItemId, int32 Count )
// {
//     return RemoveItem( ItemId, Count );
// }
//
// const TArray< FInventoryItemStack >& UInventoryComponent::GetItemStacks() const
// {
//     return Items;
// }
