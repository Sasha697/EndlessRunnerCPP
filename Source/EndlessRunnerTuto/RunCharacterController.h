// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "RunCharacterController.generated.h"

UCLASS()
class ENDLESSRUNNERTUTO_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
    ARunCharacterController();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* InputMappingContext;

    UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Enhanced Input")
    class UInputAction* MoveAction;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent();

    void EnhancedInputMove(const FInputActionValue& Value);


private:
    // Reference to the RunCharacter
    class ARunCharacter* RunCharacter;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
