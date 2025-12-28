// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FarmCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MYFARM_API AFarmCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFarmCharacter();

protected:
    virtual void BeginPlay() override;
    
    // Camera boom positioning the camera behind the character
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Camera" )
    TObjectPtr< USpringArmComponent > CameraBoom;
    
    // Follow camera
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Camera" )
    TObjectPtr< UCameraComponent > FollowCamera;

public:
    virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
};
