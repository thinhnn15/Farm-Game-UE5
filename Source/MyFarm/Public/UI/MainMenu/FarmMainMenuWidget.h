// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FarmMainMenuWidget.generated.h"

UENUM( BlueprintType )
enum class EFarmMainMenuItem : uint8
{
    Continue
    , NewGame
    , Options
    , Exit
};

class UVerticalBox;

UCLASS()
class MYFARM_API UFarmMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void MoveSelection( int32 Direction );
    void ConfirmSelection();

protected:
    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UVerticalBox > VB_MenuItems;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Menu " )
    EFarmMainMenuItem CurrentItem = EFarmMainMenuItem::NewGame;
    
    int32 CurrentIndex = 0;
    
    void UpdateVisualSelection();
};
