// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "RunCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>("AttachPoint");
	AttachPoint->SetupAttachment(SceneComponent); 

	ExitTrigger = CreateDefaultSubobject<UBoxComponent>("Collision Mesh");
	ExitTrigger->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	ExitTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);
}

void ATile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{
	// Check if we collided with a Target
	if (ARunCharacter* runCharacter = Cast<ARunCharacter>(OtherActor))
	{
		OnExitTile.Broadcast(this);
	}
}

void ATile::SpawnObstacle()
{
}

void ATile::SpawnPickup()
{
}

FVector ATile::GetAttachPointLocation()
{
	return AttachPoint->GetComponentLocation(); 
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

