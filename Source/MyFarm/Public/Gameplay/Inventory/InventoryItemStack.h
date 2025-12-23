// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemStack.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FInventoryItemStack
{
    GENERATED_BODY()

public:
    // RowId in DataTable (Seed_Carrot, Seed_Wheat,...)
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Inventory" )
    FName ItemRowId;

    // Quantity of items in this stack
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Inventory" )
    int32 Count = 0;

public:
    bool IsValid() const
    {
        return ItemRowId != NAME_None && Count > 0;
    }
};
