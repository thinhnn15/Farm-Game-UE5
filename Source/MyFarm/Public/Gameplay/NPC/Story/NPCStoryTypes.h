// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCStoryTypes.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FNPCStoryState
{
    GENERATED_BODY()
public: 
    UPROPERTY()
    FName NPCId;
    
    UPROPERTY()
    FName CurrentState;
    
    UPROPERTY()
    TSet<FName> StoryFlag;
};
