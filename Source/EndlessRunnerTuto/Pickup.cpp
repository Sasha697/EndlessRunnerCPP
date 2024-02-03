// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/SceneComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Statis Mesh"); 
	StaticMesh->SetCollisionProfileName("BlockAllDynamic");
	StaticMesh->SetSimulatePhysics(false); 
	StaticMesh->SetNotifyRigidBodyCollision(true);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Rotating Movement Component");
}

// Called when the game starts or when spawned
void APickup::BeginPlay() 
{
	Super::BeginPlay(); 
	
	StaticMesh->OnComponentHit.AddDynamic(this, &APickup::OnComponentHit); 
}

void APickup::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())  
	{ 
		OnGet(OtherActor);
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

