// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/FarmMenuEntryWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Components/Button.h"

void UFarmMenuEntryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetSelected( false );

    if ( !Btn_Root )
        return;

    Btn_Root->SetIsEnabled( false );
}

void UFarmMenuEntryWidget::SetLabelText( const FText& NewText )
{
    if ( !Txt_Label )
        return;

    Txt_Label->SetText( NewText );
}

void UFarmMenuEntryWidget::SetSelected( bool bSelected )
{
    bIsSelected = bSelected;

    if ( !Txt_Label )
        return;
    
    Txt_Label->SetRenderOpacity( bIsSelected ? SelectedOpacity : UnselectedOpacity );
}
