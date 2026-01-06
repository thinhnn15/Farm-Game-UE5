// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Character/FarmCharacter.h"
#include "Gameplay/Tool/ToolBase.h"
#include "UObject/Interface.h"
#include "FarmInteractable.generated.h"

UINTERFACE( BlueprintType )
class MYFARM_API UFarmInteractable : public UInterface
{
    GENERATED_BODY()
};

USTRUCT()
struct MYFARM_API FFarmInteractionContext
{
    GENERATED_BODY()

    UPROPERTY()
    TObjectPtr< AFarmCharacter > Instigator = nullptr;

    UPROPERTY()
    TObjectPtr< UToolBase > UsedTool = nullptr;

    UPROPERTY()
    FVector WorldLocation = FVector::ZeroVector;
};

class MYFARM_API IFarmInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact( const FFarmInteractionContext& Context ) = 0;
};
