// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FarmTimeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnDayChanged,
    int32,
    NewDay
);

UCLASS()
class MYFARM_API UFarmTimeSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable, Category = "Time" )
    void AdvanceDay();

    UPROPERTY( BlueprintAssignable, Category = "Time" )
    FOnDayChanged OnDayChanged;

    UFUNCTION( BlueprintPure, Category = "Time" )
    int32 GetCurrentDay() const;

private:
    UPROPERTY()
    int32 m_CurrentDay = 0;
};
