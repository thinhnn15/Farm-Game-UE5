// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyFarmCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 *  A controllable top-down perspective character
 */
UCLASS( abstract )
class AMyFarmCharacter : public ACharacter
{
    GENERATED_BODY()

private:
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true") )
    TObjectPtr< UCameraComponent > TopDownCameraComponent;

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true") )
    TObjectPtr< USpringArmComponent > CameraBoom;

public:
    AMyFarmCharacter();

    virtual void BeginPlay() override;

    virtual void Tick( float DeltaSeconds ) override;

    UCameraComponent* GetTopDownCameraComponent() const
    {
        return TopDownCameraComponent.Get();
    }

    USpringArmComponent* GetCameraBoom() const
    {
        return CameraBoom.Get();
    }
};
