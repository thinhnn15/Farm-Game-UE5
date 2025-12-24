// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ToolBase.generated.h"

UCLASS( Abstract, Blueprintable )
class MYFARM_API UToolBase : public UObject
{
    GENERATED_BODY()

public:
    virtual bool CanUseOnActor( AActor* TargetActor ) const
    PURE_VIRTUAL( UToolBase::CanUseOnActor, return false; );

    // Use this tool on the target actor
    virtual void UseOnActor( AActor* TargetActor )
    PURE_VIRTUAL( UToolBase::UseOnActor, );
};
