// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "BugNetTool.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UBugNetTool : public UToolBase
{
    GENERATED_BODY()
    
public:
    virtual bool CanUse(const FToolUseContext& UseContext) const override;
    virtual void Use(const FToolUseContext& UseContext) override;
};
