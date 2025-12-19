// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTypeData.generated.h"

UCLASS(Abstract, BlueprintType)
class MYFARM_API UGameplayTypeData : public UDataAsset
{
    GENERATED_BODY()
    
public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay" )
    FName TypeId;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay" )
    FText DisplayName;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay" )
    FText Description;
};
