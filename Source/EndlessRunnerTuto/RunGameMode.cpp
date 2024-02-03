// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Tile.h"
#include <Kismet/GameplayStatics.h>

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitTiles();
	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (RunCharacter == nullptr)
	{
		return;
	}
	RunCharacter->OnDeath.AddDynamic(this, &ARunGameMode::OnPlayerDeath); 
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
