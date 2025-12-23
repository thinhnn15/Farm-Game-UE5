// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/SeedItemRow.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FarmSeedSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UFarmSeedSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize( FSubsystemCollectionBase& Collection ) override;

    const FSeedItemRow* GetSeedData( FName SeedItemRowId ) const;

protected:
    UPROPERTY()
    TObjectPtr< UDataTable > SeedTable;
};
