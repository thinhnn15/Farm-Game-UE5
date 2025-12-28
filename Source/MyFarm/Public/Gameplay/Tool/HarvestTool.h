// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "HarvestTool.generated.h"

UCLASS()
class MYFARM_API UHarvestTool : public UToolBase
{
    GENERATED_BODY()

public:
    virtual bool CanUse( const FToolUseContext& UseContext ) const override;
    virtual void Use( const FToolUseContext& UseContext ) override;
};
