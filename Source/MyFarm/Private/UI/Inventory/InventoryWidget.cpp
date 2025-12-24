// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/SeedItemEntryWidget.h"
#include "Core/Data/FarmSeedSubsystem.h"
#include "Engine/GameEngine.h"

void UInventoryWidget::RefreshInventory()
{
    if ( !VBSeedList || !InventorySubsystem )
        return;

    VBSeedList->ClearChildren();
    SeedItemWidgets.Empty();

    const TMap< FName, int32 >& Items = InventorySubsystem->GetAllSeeds();
    for ( const auto& Item : Items )
    {
        const FName SeedRowId = Item.Key;
        const int32 Count = Item.Value;

        if ( Count <= 0 )
            continue;
        // UTextBlock* DebugText = NewObject< UTextBlock >( this );
        // if ( !DebugText )
        //     continue;
        //
        // DebugText->SetText(
        //     FText::FromString(
        //         FString::Printf( TEXT( "Seed: %s | Count: %d" ),
        //                          *SeedRowId.ToString(), Count )
        //     )
        // );
        //
        // DebugText->SetColorAndOpacity( FSlateColor( FLinearColor::Yellow ) );
        // // DebugText->SetFont( FSlateFontInfo(
        // //     FCoreStyle::GetDefaultFont(), 16
        // // ) );
        //
        // VBSeedList->AddChildToVerticalBox( DebugText );
        
        
        USeedItemEntryWidget* Entry = CreateWidget< USeedItemEntryWidget >( this, SeedItemEntryWidgetClass );
        if ( !Entry )
            continue;
        
        Entry->Setup( SeedRowId, Count );
        Entry->OnSeedItemClicked.AddUObject( this, &UInventoryWidget::HandleSeedSelected );
        
        VBSeedList->AddChildToVerticalBox(Entry);
        SeedItemWidgets.Add( SeedRowId, Entry );
    }

    TxtSelectedSeed->SetText( FText::FromString( "Selected: None" ) );
    SelectedSeedRowId = NAME_None;
}

FName UInventoryWidget::GetSelectedSeed() const
{
    return SelectedSeedRowId;
}

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UGameInstance* GI = GetGameInstance();
    check( GI );

    InventorySubsystem = GI->GetSubsystem< UFarmInventorySubsystem >();
    check( InventorySubsystem );

    RefreshInventory();
}

void UInventoryWidget::HandleSeedSelected( FName SeedRowId )
{
    SelectedSeedRowId = SeedRowId;

    for ( auto& Item : SeedItemWidgets )
    {
        Item.Value->SetSelected( Item.Key == SeedRowId );
    }

    TxtSelectedSeed->SetText( FText::FromString(
        FString::Printf( TEXT( "Selected: %s" ), *SeedRowId.ToString() )
    ) );

    UE_LOG( LogTemp, Log, TEXT("[InventoryWidget] Selected seed: %s"), *SeedRowId.ToString() );
}
