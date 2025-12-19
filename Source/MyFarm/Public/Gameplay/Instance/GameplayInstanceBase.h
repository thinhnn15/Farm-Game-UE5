// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayInstanceBase.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class MYFARM_API UGameplayInstanceBase : public UObject
{
    GENERATED_BODY()

public:
    // Entry point to initialize this instance
    void InitializeInstance();

    // Entry point to deinitialize this instance
    void DeinitializeInstance();

    // Is this instance initialized
    bool IsInitialized() const;

    // World context (safe helper)
    virtual UWorld* GetWorld() const override;

protected:
    // Called once when instance is initialized
    virtual void OnInitialize();

    // Called once when instance is deinitialized
    virtual void OnDeinitialize();

private:
    // Prevent double init
    bool bIsInitialized = false;
};
