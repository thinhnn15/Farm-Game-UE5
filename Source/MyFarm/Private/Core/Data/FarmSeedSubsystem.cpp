// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/FarmSeedSubsystem.h"

void UFarmSeedSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
    Super::Initialize( Collection );

    static const FString TablePath = TEXT( "/Game/MyFarm/Data/Items/Seeds/DT_SeedItems.DT_SeedItems" );
    SeedTable = LoadObject< UDataTable >( nullptr, *TablePath );
    if ( !SeedTable )
    {
        UE_LOG( LogTemp, Warning, TEXT( "Failed to load SeedTable." ) );
        return;
    }
    UE_LOG( LogTemp, Warning, TEXT( "Loaded SeedTable." ) );
}

const FSeedItemRow* UFarmSeedSubsystem::GetSeedData( FName SeedItemRowId ) const
{
    if ( !SeedTable )
        return nullptr;
    
    return SeedTable->FindRow< FSeedItemRow >( SeedItemRowId, TEXT( "GetSeedData" ) );
}
