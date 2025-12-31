// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BugDataRow.h"
#include "GameFramework/Actor.h"
#include "BugActor.generated.h"

UCLASS()
class MYFARM_API ABugActor : public AActor
{
    GENERATED_BODY()

public:
    ABugActor();

    void Init( const FDataTableRowHandle& InBugData );

    bool CanBeCaught( const FVector& PlayerLocation ) const;
    void OnCaught();
    void OnEscape();

protected:
    UPROPERTY( EditAnywhere, Category="Bug" )
    FDataTableRowHandle BugRow;

    UPROPERTY( VisibleAnywhere )
    TObjectPtr< UStaticMeshComponent > BugMesh;
};
