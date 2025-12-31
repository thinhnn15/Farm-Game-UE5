// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NPCRelationshipTypes.h"
#include "NPCRelationshipSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UNPCRelationshipSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    const FNPCRelationship* GetRelationship( FName NPCId ) const;
    void AddRelationshipPoints( FName NPCId, int32 Points );
    ERelationshipLevel GetRelationshipLevel( FName NPCId ) const;

private:
    UPROPERTY()
    TMap< FName, FNPCRelationship > Relationships;
};
