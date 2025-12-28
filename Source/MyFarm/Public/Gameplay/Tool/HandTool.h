// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "HandTool.generated.h"

UCLASS()
class MYFARM_API UHandTool : public UToolBase
{
    GENERATED_BODY()
    
public:
    virtual void Use( const FToolUseContext& Context ) override;
};
