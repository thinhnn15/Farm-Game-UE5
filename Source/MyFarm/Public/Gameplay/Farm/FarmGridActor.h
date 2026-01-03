// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmPlot.h"
#include "GameFramework/Actor.h"
#include "FarmGridActor.generated.h"

UCLASS()
class MYFARM_API AFarmGridActor : public AActor
{
    GENERATED_BODY()

public:
    AFarmGridActor();

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY( EditAnywhere, Category = "FarmGrid" )
    TSubclassOf< AFarmPlot > PlotClass;

    UPROPERTY( EditAnywhere, Category = "FarmGrid" )
    int32 Rows = 5;

    UPROPERTY( EditAnywhere, Category = "FarmGrid" )
    int32 Columns = 5;

    UPROPERTY( EditAnywhere, Category = "FarmGrid" )
    float PlotSpacing = 300.f;
};
