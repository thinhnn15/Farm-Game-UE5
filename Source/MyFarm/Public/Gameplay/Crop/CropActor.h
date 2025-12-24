// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Gameplay/Crop/CropGrowthStage.h"
#include "CropActor.generated.h"

class UCropInstance;
class UCropVisualData;
class UStaticMeshComponent;

UCLASS()
class MYFARM_API ACropActor : public AActor
{
    GENERATED_BODY()

public:
    ACropActor();

    // Bind this actor ro a crop instance
    void BindCropInstance( UCropInstance* InCropInstance );
protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnCropStageChanged( ECropGrowthStage NewStage );
    UFUNCTION()
    void OnCropHarvested();

    // Apply visual changes for stage
    void ApplyStageVisuals( ECropGrowthStage Stage );

protected:
    UPROPERTY( VisibleAnywhere )
    TObjectPtr< USceneComponent > Root;

    // Mesh representing the crop
    UPROPERTY( VisibleAnywhere )
    TObjectPtr< UStaticMeshComponent > MeshComponent;

    // Runtime crop instance (logic)
    UPROPERTY()
    TObjectPtr< UCropInstance > CropInstance;

    // Cached visual data (from CropTypeData)
    UPROPERTY()
    TObjectPtr< UCropVisualData > CropVisualData;
};
