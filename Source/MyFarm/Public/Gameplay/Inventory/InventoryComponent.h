// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "Components/ActorComponent.h"
// #include "InventoryItemStack.h"
// #include "InventoryComponent.generated.h"
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventoryChanged );
//
// UCLASS( ClassGroup=(Farm), meta=(BlueprintSpawnableComponent) )
// class MYFARM_API UInventoryComponent : public UActorComponent
// {
//     GENERATED_BODY()
//
// public:
//     // Query
//     UFUNCTION( BlueprintPure )
//     int32 GetItemCount( FName ItemId ) const;
//
//     // Modify
//     UFUNCTION( BlueprintCallable )
//     bool AddItem( FName ItemId, int32 Count );
//
//     UFUNCTION( BlueprintCallable )
//     bool RemoveItem( FName ItemId, int32 Count );
//
//     UFUNCTION( BlueprintCallable )
//     bool ConsumeItem( FName ItemId, int32 Count );
//
//     // Debug
//     UFUNCTION( BlueprintPure )
//     const TArray< FInventoryItemStack >& GetItemStacks() const;
//
// public:
//     UPROPERTY( BlueprintAssignable )
//     FOnInventoryChanged OnInventoryChanged;
//
// protected:
//     UPROPERTY()
//     TArray< FInventoryItemStack > Items;
// };
