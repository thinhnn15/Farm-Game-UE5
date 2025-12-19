// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gameplay/Instance/GameplayInstanceBase.h"

void UGameplayInstanceBase::InitializeInstance()
{
    if ( bIsInitialized )
    {
        UE_LOG( LogTemp, Warning, TEXT( "[GameplayInstance] Instance '%s' is already initialized!" ), *GetName() );
        return;
    }

    bIsInitialized = true;
    OnInitialize();
}

void UGameplayInstanceBase::DeinitializeInstance()
{
    if ( !bIsInitialized )
        return;

    OnDeinitialize();
    bIsInitialized = false;
}

bool UGameplayInstanceBase::IsInitialized() const
{
    return bIsInitialized;
}

UWorld* UGameplayInstanceBase::GetWorld() const
{
    const UObject* Outer = GetOuter();
    if ( !Outer )
        return nullptr;
    
    return Outer->GetWorld();
}

void UGameplayInstanceBase::OnInitialize()
{
}

void UGameplayInstanceBase::OnDeinitialize()
{
}
