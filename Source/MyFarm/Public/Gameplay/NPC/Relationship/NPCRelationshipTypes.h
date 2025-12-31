// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCRelationshipTypes.generated.h"

UENUM( BlueprintType )
enum class ERelationshipLevel : uint8
{
    Stranger UMETA( DisplayName="Stranger" )
    , Acquaintance UMETA( DisplayName="Acquaintance" )
    , Friend UMETA( DisplayName="Friend" )
    , CloseFriend UMETA( DisplayName="Close Friend" )
    , BestFriend UMETA( DisplayName="Best Friend" )
    , Soulmate UMETA( DisplayName="Soulmate" )
};

USTRUCT( BlueprintType )
struct MYFARM_API FNPCRelationship
{
    GENERATED_BODY( )
    
    UPROPERTY()
    FName NPCId;
    
    UPROPERTY()
    int32 RelationShipPoints = 0;
    
    UPROPERTY()
    ERelationshipLevel Level = ERelationshipLevel::Stranger;
};
