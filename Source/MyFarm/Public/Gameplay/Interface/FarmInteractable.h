// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Gameplay/Interaction/FarmInteractionContext.h"
#include "FarmInteractable.generated.h"

UINTERFACE( BlueprintType )
class MYFARM_API UFarmInteractable : public UInterface
{
    GENERATED_BODY()
};

class MYFARM_API IFarmInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact( const FFarmInteractionContext& Context ) = 0;
};
