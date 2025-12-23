// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmPlot.generated.h"

class UCropInstance;
class UCropTypeData;
class ACropActor;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class MYFARM_API AFarmPlot : public AActor
{
    GENERATED_BODY()

public:
    AFarmPlot();
    // Can we plant a new crop here?
    UFUNCTION( BlueprintCallable, Category = "Farm" )
    bool CanPlant() const;

    // Plant a crop into this plot
    UFUNCTION( BlueprintCallable, Category = "Farm" )
    bool PlantCrop( FName CropRowId );

    void ClearCrop();

    // Try to harvest the crop in this plot
    UFUNCTION( BlueprintCallable, Category = "Farm" )
    bool TryHarvest();

protected:
    virtual void BeginPlay() override;

protected:
    // Actor class for visual
    UPROPERTY( EditAnywhere, Category="Crop" )
    TSubclassOf< ACropActor > CropActorClass;

    // Runtime
    // Logic
    UPROPERTY()
    TObjectPtr< UCropInstance > CropInstance;

    // Visual
    UPROPERTY()
    TObjectPtr< ACropActor > CropActor;

    // Component
    UPROPERTY( VisibleAnywhere, Category="Components" )
    TObjectPtr< UBoxComponent > PlotCollision;

    UPROPERTY( VisibleAnywhere, Category="Components" )
    TObjectPtr< UStaticMeshComponent > PlotMesh;
};
