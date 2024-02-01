// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetCollidedSignature, ATile*, Tile);

UCLASS()
class ENDLESSRUNNERTUTO_API ATile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FTargetCollidedSignature OnTargetCollided;
	
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

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTransform GetAttachPointTransform();

};
