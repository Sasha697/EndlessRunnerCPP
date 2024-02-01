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

	OnActorHit.AddDynamic(this, &ATile::OnHit);
}

void ATile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if we collided with a Target
	if (ARunCharacter* runCharacter = Cast<ARunCharacter>(OtherActor))
	{
		OnTargetCollided.Broadcast(this);
	}
}

FTransform ATile::GetAttachPointTransform()
{
	return AttachPoint->GetComponentTransform(); 
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

