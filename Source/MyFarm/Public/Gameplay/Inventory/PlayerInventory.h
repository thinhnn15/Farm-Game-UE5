// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UPlayerInventory : public UObject
{
    GENERATED_BODY()
    
public:
    // Set the currently selected seed for planting
    void SetSelectedSeed( FName SeedRowId );
    
    bool HasSeed() const;
    FName GetSelectedSeed() const;
    void ConsumeSeed();
    
private:
    // Currently selected seed for planting
    UPROPERTY()
    FName SelectedSeedRowId = NAME_None;
};
