// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERTUTO_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TSubclassOf<class ATile> TileClass;

	FVector myLoc = FVector::ZeroVector;

	UFUNCTION()
	void SpawnNextTiles(ATile* PreviousTile);
	UFUNCTION()
	void DestroyTile(ATile* ExitedTile);
	ATile* LastTile;

private:
    // Reference to the RunCharacter
    class ARunCharacter* RunCharacter;
	void InitTiles();

};
