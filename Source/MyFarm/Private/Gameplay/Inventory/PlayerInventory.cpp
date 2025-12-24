// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Inventory/PlayerInventory.h"

void UPlayerInventory::SetSelectedSeed( FName SeedRowId )
{
    SelectedSeedRowId = SeedRowId;
}

bool UPlayerInventory::HasSeed() const
{
    return !SelectedSeedRowId.IsNone();
}

FName UPlayerInventory::GetSelectedSeed() const
{
    return SelectedSeedRowId;
}

void UPlayerInventory::ConsumeSeed()
{
    SelectedSeedRowId = NAME_None;
}
