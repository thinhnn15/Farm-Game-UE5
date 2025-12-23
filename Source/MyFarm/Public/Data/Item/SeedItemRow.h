// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SeedItemRow.generated.h"

USTRUCT( BlueprintType )
struct FSeedItemRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Crop type this seed grows into
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Seed" )
    FName CropRowId;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Seed" )
    FText DisplayName;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Seed" )
    TObjectPtr< UTexture2D > Icon;
};
