// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CropTestSpawner.generated.h"

class UCropTypeData;
class UCropInstance;
class ACropActor;

UCLASS()
class MYFARM_API ACropTestSpawner : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    
public:
    UPROPERTY( EditAnywhere, category = "Test" )
    TObjectPtr< UCropTypeData > TestCropType;
    
    UPROPERTY( EditAnywhere, category = "Test" )
    TSubclassOf< ACropActor > CropActorClass;
};
