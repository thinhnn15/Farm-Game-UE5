// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFishingState.generated.h"

UENUM( BlueprintType )
enum class EFishingState : uint8
{
    Idle UMETA( DisplayName="Idle" )
    , Casting UMETA( DisplayName="Casting" )
    , WaitingForBite UMETA( DisplayName="WaitingForBite" )
    , Bite UMETA( DisplayName="Bite" )
    , Hooked UMETA( DisplayName="Hooked" )
    , Success UMETA( DisplayName="Success" )
    , Failed UMETA( DisplayName="Failed" )
};
