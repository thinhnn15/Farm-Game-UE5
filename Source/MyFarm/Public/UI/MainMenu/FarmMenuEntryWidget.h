// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FarmMenuEntryWidget.generated.h"


class UTextBlock;
class UButton;

UCLASS()
class MYFARM_API UFarmMenuEntryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION( BlueprintCallable )
    void SetLabelText( const FText& NewText );

    UFUNCTION( BlueprintCallable )
    void SetSelected( bool bIsSelected );

protected:
    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UButton > Btn_Root;

    UPROPERTY( meta = (BindWidget) )
    TObjectPtr< UTextBlock > Txt_Label;

    // Style
    UPROPERTY( EditAnywhere, Category = "Style" )
    float UnselectedOpacity = 0.6f;

    UPROPERTY( EditAnywhere, Category = "Style" )
    float SelectedOpacity = 1.0f;

private:
    bool bIsSelected = false;
};
