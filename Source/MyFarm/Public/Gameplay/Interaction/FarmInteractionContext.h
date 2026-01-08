#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "FarmInteractionContext.generated.h"

USTRUCT( BlueprintType )
struct MYFARM_API FFarmInteractionContext
{
    GENERATED_BODY()

public:
    // Player controller who initiated the interaction
    UPROPERTY()
    TObjectPtr< APlayerController > InstigatorController = nullptr;

    // Pawn controlled by the player
    UPROPERTY()
    TObjectPtr< APawn > InstigatorPawn = nullptr;

    // Target actor being interacted with
    UPROPERTY()
    TObjectPtr< AActor > TargetActor = nullptr;

    // Full hit result from trace
    UPROPERTY()
    FHitResult HitResult;

    // Cached world location
    UPROPERTY()
    FVector WorldLocation = FVector::ZeroVector;

    // Cached world normal
    UPROPERTY()
    FVector WorldNormal = FVector::ZeroVector;

    // Primary / Secondary action
    UPROPERTY()
    bool bIsPrimaryAction = true;

    // Continuous usage (holding button)
    UPROPERTY()
    bool bIsContinuousUse = false;

public:
    // ===== Helper API =====

    bool HasValidHit() const
    {
        return HitResult.bBlockingHit;
    }

    EPhysicalSurface GetSurfaceType() const
    {
        if ( HitResult.PhysMaterial.IsValid() )
        {
            return HitResult.PhysMaterial->SurfaceType;
        }
        return SurfaceType_Default;
    }
};
