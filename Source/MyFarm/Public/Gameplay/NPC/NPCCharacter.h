// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class MYFARM_API ANPCCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere )
    FName NPCId;
    
    void TalkToPlayer();
};
