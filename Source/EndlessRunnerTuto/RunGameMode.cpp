// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Tile.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitTiles();
}

void ARunGameMode::InitTiles()
{
	LastTile = nullptr;
	int32 length = 10;
	for (size_t i = 0; i < length; i++)
	{
		SpawnNextTiles(LastTile);
	}
}

void ARunGameMode::SpawnNextTiles(ATile* PreviousTile)
{
	FActorSpawnParameters SpawnInfo;
	LastTile = GetWorld()->SpawnActor<ATile>(TileClass, myLoc, FRotator::ZeroRotator, SpawnInfo);
	if (LastTile)
	{
		myLoc = LastTile->GetAttachPointLocation();
		LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::SpawnNextTiles);
		LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::DestroyTile);
	}
		
}

void ARunGameMode::DestroyTile(ATile* ExitedTile)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ExitedTile]()
	{
		ExitedTile->Destroy();
	}, 2.5f, false);
}
