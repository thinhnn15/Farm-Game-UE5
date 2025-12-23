// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/FarmCropDataSubsystem.h"
#include "Public/Data/CropTypeRow.h"

const FCropTypeRow* UFarmCropDataSubsystem::GetCropData( FName CropRowId ) const
{
    if ( !CropTypeDataTable )
        return nullptr;
    
    return CropTypeDataTable->FindRow< FCropTypeRow >( CropRowId, TEXT( "UFarmCropDataSubsystem::GetCropTypeData" ) );
}
