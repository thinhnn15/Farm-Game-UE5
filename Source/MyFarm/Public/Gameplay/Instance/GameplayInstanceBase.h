// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFARM_API UGameplayInstanceBase : public UObject
{
    GENERATED_BODY()

public:
    virtual void Initialize() {}
    virtual void Deinitialize() {}
};
