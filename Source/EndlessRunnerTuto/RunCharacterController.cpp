// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacterController.h"
#include "RunCharacter.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

ARunCharacterController::ARunCharacterController()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void ARunCharacterController::BeginPlay()
{
    Super::BeginPlay();

    // Get a reference to the RunCharacter
	RunCharacter = Cast<ARunCharacter>(GetPawn());
	//Add Input Mapping Context
	if (RunCharacter)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	SetupPlayerInputComponent();
}

void ARunCharacterController::Tick(float DeltaTime)
{
	FVector forwardVector = FVector(1.0f, 0.0f, 0.0f);
	RunCharacter->AddMovementInput(forwardVector);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARunCharacterController::SetupPlayerInputComponent()
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunCharacterController::EnhancedInputMove);
	}
}

void ARunCharacterController::EnhancedInputMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();
	FVector rightVector = FVector(0.0f, 1.0f, 0.0f);
	// add movement 
	RunCharacter->AddMovementInput(rightVector, movementVector.X);
}

