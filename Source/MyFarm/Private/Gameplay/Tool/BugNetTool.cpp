// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Tool/BugNetTool.h"

#include "Gameplay/Bug/BugActor.h"

bool UBugNetTool::CanUse( const FToolUseContext& UseContext ) const
{
    return Cast< ABugActor >( UseContext.TargetActor ) != nullptr;
}

void UBugNetTool::Use( const FToolUseContext& UseContext )
{
    ABugActor* Bug = Cast< ABugActor >( UseContext.TargetActor );
    if ( !Bug )
        return;

    const bool bSuccess = Bug->CanBeCaught( UseContext.InstigatorPawn->GetActorLocation() );
    if ( bSuccess )
        Bug->OnCaught();
    else
        Bug->OnEscape();
}
