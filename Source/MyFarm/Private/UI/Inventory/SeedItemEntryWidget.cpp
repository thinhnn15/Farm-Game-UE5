// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/SeedItemEntryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"

void USeedItemEntryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    check( BtnSeedItem );
    BtnSeedItem->OnClicked.AddDynamic( this, &USeedItemEntryWidget::HandleButtonClicked );
}

void USeedItemEntryWidget::HandleButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT( "SeedItemEntryWidget::HandleButtonClicked" ) );
    OnSeedItemClicked.Broadcast( SeedRowId );
}

void USeedItemEntryWidget::Setup( FName InSeedRowId, int32 InQuantity )
{
    SeedRowId = InSeedRowId;
    Count = InQuantity;

    TxtSeedName->SetText( FText::FromName( SeedRowId ) );
    TxtCount->SetText( FText::FromString( FString::Printf( TEXT( "x%d" ), Count ) ) );

    SetEnabled( Count > 0 );
    SetSelected( false );
}

void USeedItemEntryWidget::SetSelected( bool bIsSelected )
{
    if ( !BorderSelected )
        return;
    
    BorderSelected->SetBrushColor(
        bIsSelected
            ? FLinearColor(0.2f, 0.6f, 1.f, 0.35f)   // selected
            : FLinearColor(1.f, 1.f, 1.f, 0.f)      // not selected
    );
}

void USeedItemEntryWidget::SetEnabled( const bool bEnable )
{
    BtnSeedItem->SetIsEnabled( bEnable );
}
