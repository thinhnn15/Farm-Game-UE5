// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "FarmPlotVisualData.generated.h"

USTRUCT( Blueprintable )
struct MYFARM_API FFarmPlotStateVisual
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    TObjectPtr< UMaterialInterface > SoilMaterial = nullptr;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    TObjectPtr< UNiagaraSystem > EnterStateX = nullptr;

    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    bool bEnableHighlight = false;

};
