// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FarmCropDataSubsystem.generated.h"

struct FCropTypeRow;

/**
 * 
 */
UCLASS()
class MYFARM_API UFarmCropDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    const FCropTypeRow* GetCropData( FName CropRowId ) const;

protected:
    UPROPERTY( EditDefaultsOnly, Category = "Data" )
    TObjectPtr< UDataTable > CropTypeDataTable;
};
