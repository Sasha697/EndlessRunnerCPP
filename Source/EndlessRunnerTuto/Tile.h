// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetCollidedSignature, ATile*, ExitedTile);

UCLASS()
class ENDLESSRUNNERTUTO_API ATile : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UBoxComponent* ExitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ObstacleSpawnArea")
	UBoxComponent* ObstacleSpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickupSpawnArea")
	UBoxComponent* PickupSpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	TArray<TSubclassOf<class AObstacle>> ObstaclesTypes;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TArray<TSubclassOf<class APickup>> Pickups;*/


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION(BlueprintCallable, Category = "Obstacle")
	void SpawnObstacle();

	UFUNCTION()
	void SpawnPickup();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetAttachPointLocation();

	UPROPERTY(BlueprintAssignable)
	FTargetCollidedSignature OnExitTile;
};
