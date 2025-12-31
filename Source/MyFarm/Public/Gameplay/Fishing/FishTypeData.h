// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FishTypeData.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FFishTypeRow
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    FName FishId;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    int32 MinBiteTime = 2;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    int32 MaxBiteTime = 5;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    float CatchDifficulty = 0.3f;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    int32 SellPrice = 10;
};
