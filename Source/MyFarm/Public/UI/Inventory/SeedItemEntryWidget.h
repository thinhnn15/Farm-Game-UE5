// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SeedItemEntryWidget.generated.h"

class UButton;
class UTextBlock;
class UBorder;

DECLARE_MULTICAST_DELEGATE_OneParam( FOnSeedItemCliked, FName /*SeedItemRowId*/ );

/**
 * 
 */
UCLASS()
class MYFARM_API USeedItemEntryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Setup data for this entry
    void Setup( FName InSeedRowId, int32 InQuantity );

    // Visual states
    void SetSelected( bool bIsSelected );
    void SetEnabled( bool bIsEnabled );

    // Event for parent widget
    FOnSeedItemCliked OnSeedItemClicked;

protected:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void HandleButtonClicked();

protected:
    // BindWidget (Blueprint mus have correct name)
    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UButton > BtnSeedItem;

    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UTextBlock > TxtSeedName;

    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UTextBlock > TxtCount;

    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UBorder > BorderSelected;

private:
    FName SeedRowId;
    int32 Count = 0;
};
