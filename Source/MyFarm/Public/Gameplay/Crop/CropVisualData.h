// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropVisualData.generated.h"

class UNiagaraSystem;

USTRUCT( BlueprintType )
struct FCropStageVisual
{
    GENERATED_BODY()

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    TObjectPtr< UStaticMesh > Mesh;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    TObjectPtr< UMaterialInterface > Material;

    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual" )
    TObjectPtr< UNiagaraSystem > EnterStageFX;
};

UCLASS( BlueprintType )
class MYFARM_API UCropVisualData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
    TMap< ECropGrowthStage, FCropStageVisual > StageVisuals;

    const FCropStageVisual* GetVisual( ECropGrowthStage Stage ) const;
};
