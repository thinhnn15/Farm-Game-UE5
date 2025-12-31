// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BugType.generated.h"

UENUM( BlueprintType )
enum class EBugType : uint8
{
    Butterfly
    , Grasshopper
    , Cricket
    , Beetle
};
