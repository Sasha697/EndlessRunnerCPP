// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "RunCharacter.h"
#include "Obstacle.h"
#include "Pickup.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/KismetMathLibrary.h>

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

	ObstacleSpawnArea = CreateDefaultSubobject<UBoxComponent>("ObstacleSpawnArea");
	ObstacleSpawnArea->SetupAttachment(SceneComponent);

	PickupSpawnArea = CreateDefaultSubobject<UBoxComponent>("PickupSpawnArea");
	PickupSpawnArea->SetupAttachment(SceneComponent);


}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SpawnObstacle();
	SpawnPickup();
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
	if (UKismetMathLibrary::RandomBoolWithWeight(0.6f))
	{
		if (ObstaclesTypes.Num() <= 0)
			return;
		const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(ObstacleSpawnArea->GetRelativeLocation(), ObstacleSpawnArea->GetScaledBoxExtent());
		const int32 RandomIndex = FMath::RandRange(0, ObstaclesTypes.Num() - 1);
		const TSubclassOf<AObstacle> RandomObstacleClass = ObstaclesTypes[RandomIndex];

		if (!RandomObstacleClass)
			return;

		UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this, "Obstacle");
		ChildActorComponent->SetChildActorClass(RandomObstacleClass);
		ChildActorComponent->RegisterComponent();
		ChildActorComponent->SetRelativeTransform(UKismetMathLibrary::Conv_VectorToTransform(SpawnLocation));
		ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ATile::SpawnPickup()
{
	if (UKismetMathLibrary::RandomBoolWithWeight(0.3f))
	{
		if (PickupsTypes.Num() <= 0)
			return;
		const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(PickupSpawnArea->GetRelativeLocation(), PickupSpawnArea->GetScaledBoxExtent());
		const int32 RandomIndex = FMath::RandRange(0, PickupsTypes.Num() - 1);
		const TSubclassOf<APickup> RandomPickupClass = PickupsTypes[RandomIndex];

		if (!RandomPickupClass)
			return;

		UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this, "Obstacle"); 
		ChildActorComponent->SetChildActorClass(RandomPickupClass); 
		ChildActorComponent->RegisterComponent(); 
		ChildActorComponent->SetRelativeTransform(UKismetMathLibrary::Conv_VectorToTransform(SpawnLocation)); 
		ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform); 
	}
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

