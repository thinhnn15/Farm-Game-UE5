// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCStoryTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NPCStorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UNPCStorySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    FName GetStoryNameState( FName NPCId ) const;
    void SetStoryState( FName NPCId, FName StoryState );

    bool HasStoryFlag( FName NPCId, FName Flag ) const;
    void SetStoryFlag( FName NPCId, FName Flag );

private:
    UPROPERTY()
    TMap< FName, FNPCStoryState > StoryStates;
};
