// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/FarmMainMenuWidget.h"
#include "UI/MainMenu/FarmMenuEntryWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Widget.h"
#include "Kismet/KismetSystemLibrary.h"

static FText GetMenuItemText( EFarmMainMenuItem MenuItem )
{
    const UEnum* Enum = StaticEnum< EFarmMainMenuItem >();
    if ( !Enum )
        return FText::FromString( "Unknown" );

    return Enum->GetDisplayNameTextByValue( static_cast< int64 >( MenuItem ) );
}

void UFarmMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    check( VB_MenuItems );

    VB_MenuItems->ClearChildren();
    MenuEntries.Empty();

    const UEnum* Enum = StaticEnum< EFarmMainMenuItem >();
    const int32 NumItems = Enum->NumEnums() - 1; // Exclude _MAX
    for ( int32 i = 0; i < NumItems; i++ )
    {
        EFarmMainMenuItem MenuItem = static_cast< EFarmMainMenuItem >( i );
        UFarmMenuEntryWidget* EntryWidget = CreateWidget< UFarmMenuEntryWidget >( this, MenuEntryWidgetClass );
        if ( !EntryWidget )
            continue;

        EntryWidget->SetLabelText( GetMenuItemText( MenuItem ) );

        VB_MenuItems->AddChild( EntryWidget );
        MenuEntries.Add( EntryWidget );
    }

    CurrentIndex = 0;
    UpdateVisualSelection();
}

void UFarmMainMenuWidget::MoveSelection( int32 Direction )
{
    if ( MenuEntries.Num() == 0 )
        return;

    CurrentIndex =
        ( CurrentIndex + Direction + MenuEntries.Num() ) % MenuEntries.Num();

    UpdateVisualSelection();
}

void UFarmMainMenuWidget::ConfirmSelection()
{
    switch ( static_cast< EFarmMainMenuItem >( CurrentIndex ) )
    {
    case EFarmMainMenuItem::Continue:
        UE_LOG( LogTemp, Log, TEXT("Continue Game") );
        break;

    case EFarmMainMenuItem::NewGame:
        UE_LOG( LogTemp, Log, TEXT("New Game") );
        break;

    case EFarmMainMenuItem::Options:
        UE_LOG( LogTemp, Log, TEXT("Options") );
        break;

    case EFarmMainMenuItem::Exit:
        UE_LOG( LogTemp, Log, TEXT("Exit Game") );
        break;

    default:
        break;
    }
}

void UFarmMainMenuWidget::UpdateVisualSelection()
{
    if ( !VB_MenuItems )
        return;

    for ( int32 i = 0; i < MenuEntries.Num(); ++i )
    {
        MenuEntries[ i ]->SetSelected( i == CurrentIndex );
    }
}
