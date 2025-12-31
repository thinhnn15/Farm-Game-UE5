// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Bug/BugActor.h"


ABugActor::ABugActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ABugActor::Init( const FDataTableRowHandle& InBugData )
{
    BugRow = InBugData;
    const FBugDataRow* BugData = BugRow.GetRow< FBugDataRow >( TEXT( "BugInit" ) );
    if ( !BugData )
        return;
    
    UE_LOG( LogTemp, Warning, TEXT("BugActor::Init()") );
}

bool ABugActor::CanBeCaught( const FVector& PlayerLocation ) const
{
    const FBugDataRow* BugData = BugRow.GetRow<FBugDataRow>(TEXT("BugCatch"));
    if (!BugData)
        return false;

    const float Distance = FVector::Dist(PlayerLocation, GetActorLocation());
    if (Distance > BugData->EscapeDistance)
    {
        return false;
    }

    const float Roll = FMath::FRand(); // 0..1
    if (Roll > (1.f - BugData->CatchDifficulty))
    {
        return false;
    }

    return true;
}

void ABugActor::OnCaught()
{
    UE_LOG( LogTemp, Warning, TEXT("BugActor::OnCaught()") );
    Destroy();
}

void ABugActor::OnEscape()
{
    UE_LOG( LogTemp, Warning, TEXT("BugActor::OnEscape()") );
    Destroy();
}
