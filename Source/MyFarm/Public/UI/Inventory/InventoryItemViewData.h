// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemViewData.generated.h"

USTRUCT( BlueprintType )
struct FInventoryItemViewData
{
    GENERATED_BODY()

public:
    UPROPERTY( BlueprintReadOnly )
    FName ItemRowId;

    UPROPERTY( BlueprintReadOnly )
    int32 Quantity;
};
