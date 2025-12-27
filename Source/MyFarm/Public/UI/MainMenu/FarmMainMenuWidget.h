// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FarmMenuEntryWidget.h"
#include "FarmMainMenuWidget.generated.h"

UENUM( BlueprintType )
enum class EFarmMainMenuItem : uint8
{
    Continue UMETA( DisplayName="Continue" )
    , NewGame UMETA( DisplayName="New Game" )
    , Options UMETA( DisplayName="Options" )
    , Exit UMETA( DisplayName="Exit" )
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
    void UpdateVisualSelection();

protected:
    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UVerticalBox > VB_MenuItems;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Menu " )
    EFarmMainMenuItem CurrentItem = EFarmMainMenuItem::NewGame;

    UPROPERTY( EditAnywhere, Category = "Menu" )
    TSubclassOf< UFarmMenuEntryWidget > MenuEntryWidgetClass;

    TArray< TObjectPtr< UFarmMenuEntryWidget > > MenuEntries;
    int32 CurrentIndex = 0;
    
protected:
    void QuitGame();
};
