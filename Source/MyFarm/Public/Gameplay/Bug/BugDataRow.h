// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BugHabitatType.h"
#include "BugType.h"
#include "BugDataRow.generated.h"

USTRUCT( BlueprintType )
struct FBugDataRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintType )
    FName BugId;
    
    UPROPERTY( EditAnywhere, BlueprintType )
    FText DisplayName;
    
    UPROPERTY( EditAnywhere, BlueprintType )
    EBugType BugType;
    
    UPROPERTY( EditAnywhere, BlueprintType )
    EBugHabitatType HabitatType;
    
    UPROPERTY( EditAnywhere, BlueprintType )
    float CatchDifficulty = 0.3f;
    
    UPROPERTY(EditAnywhere, BlueprintType )
    float EscapeDistance = 300.f;
    
    UPROPERTY( EditAnywhere, BlueprintType )
    int32 SellPrice = 5;

};
