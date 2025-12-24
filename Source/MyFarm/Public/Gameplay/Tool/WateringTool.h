// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "WateringTool.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UWateringTool : public UToolBase
{
    GENERATED_BODY()
    
public:
    virtual bool CanUseOnActor( AActor* TargetActor ) const override;
    virtual void UseOnActor( AActor* TargetActor ) override;
};
