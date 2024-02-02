// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Tile.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();


	if (ARunCharacter* runCharacter = Cast<ARunCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		// Listen to the event
		//runCharacter->OnTargetCollided.AddDynamic(this, &ASampleGameMode::OnTargetCollided);
	}
	InitTiles();
}

void ARunGameMode::InitTiles()
{
	LastTile = nullptr;
	int32 length = 5;
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
		UE_LOG(LogTemp, Warning, TEXT("plop"));
	}
		
}

void ARunGameMode::DestroyTile(ATile* ExitedTile)
{
	UE_LOG(LogTemp, Warning, TEXT("Kaboom"));
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ExitedTile]()
	{
		UE_LOG(LogTemp, Warning, TEXT("boom"));
		ExitedTile->Destroy();
	}, 2.5f, false);
}
