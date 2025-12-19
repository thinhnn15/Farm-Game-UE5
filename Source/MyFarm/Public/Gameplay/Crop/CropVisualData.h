// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "CropVisualData.generated.h"

class UNiagaraSystem;

USTRUCT( BlueprintType )
struct FCropStageVisual
{
    GENERATED_BODY()

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    UStaticMesh* Mesh = nullptr;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    UMaterialInterface* Material = nullptr;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    UNiagaraSystem* EnterStageFX = nullptr;
};
