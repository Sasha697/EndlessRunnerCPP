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
	FActorSpawnParameters SpawnInfo; 
	FRotator myRot(0, 0, 0); 
	FVector myLoc(0, 0, 0);
	int32 length = 10;
	for (size_t i = 0; i < length; i++)
	{
		ATile* Tile = GetWorld()->SpawnActor<ATile>(myLoc, myRot, SpawnInfo);
		myLoc = Tile->GetAttachPointTransform().GetLocation();
	}
}
