// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/FarmCropDataSubsystem.h"
#include "Public/Data/CropTypeRow.h"

const FCropTypeRow* UFarmCropDataSubsystem::GetCropData( FName CropRowId ) const
{
    if ( !CropTypeDataTable )
        return nullptr;

    return CropTypeDataTable->FindRow< FCropTypeRow >( CropRowId, TEXT( "UFarmCropDataSubsystem::GetCropTypeData" ) );
}

void UFarmCropDataSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
    Super::Initialize( Collection );

    static const FString CropTablePath = TEXT( "/Game/MyFarm/Data/Crops/DT_CropTypes.DT_CropTypes" );
    CropTypeDataTable = Cast< UDataTable >(
        StaticLoadObject(
            UDataTable::StaticClass(),
            nullptr,
            *CropTablePath
        )
    );

    if ( !CropTypeDataTable )
    {
        UE_LOG( LogTemp, Error, TEXT("[FarmCropDataSubsystem] Failed to load CropTypeDataTable at path: %s"), *CropTablePath );
        return;
    }

    UE_LOG( LogTemp, Log, TEXT("[FarmCropDataSubsystem] Successfully loaded CropTypeDataTable.") );
}
