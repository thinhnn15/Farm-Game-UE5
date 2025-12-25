// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Public/Gameplay/Tool/ToolUseContext.h"
#include "ToolBase.generated.h"

UCLASS( Abstract, Blueprintable )
class MYFARM_API UToolBase : public UObject
{
    GENERATED_BODY()

public:
    virtual bool CanUse( const FToolUseContext& UseContext ) const
    {
        return true;
    }

    // Use this tool on the target actor
    virtual void Use( const FToolUseContext& Context )
    PURE_VIRTUAL( UToolBase::UseOnActor, );
};
