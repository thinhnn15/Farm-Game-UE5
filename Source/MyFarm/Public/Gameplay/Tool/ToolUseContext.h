// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolUseContext.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FToolUseContext
{
    GENERATED_BODY()

public:
    // Player controller who initiated the tool usage
    UPROPERTY()
    TObjectPtr< APlayerController > InstigatorController = nullptr;

    // Pawn controlled by the player
    UPROPERTY()
    TObjectPtr< APawn > InstigatorPawn = nullptr;

    // Target actor the tool is being used on
    UPROPERTY()
    TObjectPtr< AActor > TargetActor = nullptr;

    // Full hit result from raycast under cursor
    UPROPERTY()
    FHitResult HitResult;

    // World location where the tool is used
    UPROPERTY()
    FVector WorldLocation = FVector::ZeroVector;

    // World normal at the hit location
    UPROPERTY()
    FVector WorldNormal = FVector::ZeroVector;

    // Input type (mouse, keyboard, gamepad, etc.)
    UPROPERTY()
    FName InputSource = NAME_None;

    // Whether this use was a primary action (e.g., left-click) or secondary action (e.g., right-click)
    UPROPERTY()
    bool bIsPrimaryAction = true;

    // Whether this use was continuous (e.g., holding down button) or discrete (single press)
    UPROPERTY()
    bool bIsContinuousUse = false;

public:
    bool HasValidHit() const
    {
        return HitResult.bBlockingHit;
    }

    EPhysicalSurface GetSurfaceType() const
    {
        if ( HitResult.PhysMaterial.IsValid() )
            return HitResult.PhysMaterial->SurfaceType;

        return SurfaceType_Default;
    }
};
