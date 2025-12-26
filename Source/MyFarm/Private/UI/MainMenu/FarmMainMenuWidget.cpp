// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/FarmMainMenuWidget.h"
#include "UI/MainMenu/FarmMenuEntryWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Widget.h"
#include "Kismet/KismetSystemLibrary.h"

void UFarmMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    CurrentIndex = 0;
    const TArray< FText > MenuTexts =
    {
        FText::FromString( "Continue" ), FText::FromString( "New Game" ), FText::FromString( "Options" ), FText::FromString( "Exit" )
    };

    for ( int32 i = 0; i < VB_MenuItems->GetChildrenCount(); ++i )
    {
        if ( UFarmMenuEntryWidget* Entry =
            Cast< UFarmMenuEntryWidget >( VB_MenuItems->GetChildAt( i ) ) )
        {
            Entry->SetLabelText( MenuTexts[ i ] );
        }
    }
    UpdateVisualSelection();
}

void UFarmMainMenuWidget::MoveSelection( int32 Direction )
{
    if ( !VB_MenuItems )
        return;

    const int32 Count = VB_MenuItems->GetChildrenCount();
    CurrentIndex = FMath::Clamp( CurrentIndex + Direction, 0, Count - 1 );

    UpdateVisualSelection();
}

void UFarmMainMenuWidget::ConfirmSelection()
{
    switch ( CurrentIndex )
    {
    case 0: // Continue
        UE_LOG( LogTemp, Log, TEXT("Continue selected") );
        break;
    case 1: // New Game
        UE_LOG( LogTemp, Log, TEXT("Cancel selected") );
        break;
    case 2: // Options
        UE_LOG( LogTemp, Log, TEXT("Confirm selected") );
        break;
    case 3: // Exit
        UKismetSystemLibrary::QuitGame( this, GetOwningPlayer(), EQuitPreference::Quit, false );
        break;
    default:
        UE_LOG( LogTemp, Log, TEXT("Invalid selection") );
        break;
    }
}

void UFarmMainMenuWidget::UpdateVisualSelection()
{
    if ( !VB_MenuItems )
        return;

    for ( int32 i = 0; i < VB_MenuItems->GetChildrenCount(); i++ )
    {
        if ( UWidget* Child = VB_MenuItems->GetChildAt( i ) )
        {
            Child->SetRenderOpacity( i == CurrentIndex ? 1.f : 0.6f );
        }
    }
}
