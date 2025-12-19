// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "DayAdvanceListener.generated.h"

UINTERFACE( BlueprintType )
class MYFARM_API UDayAdvanceListener : public UInterface
{
    GENERATED_BODY()
};

class MYFARM_API IDayAdvanceListener
{
    GENERATED_BODY()

public:
    virtual void OnDayAdvanced( int32 NewDay ) = 0;
};
