// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerTutoGameMode.h"
#include "EndlessRunnerTutoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerTutoGameMode::AEndlessRunnerTutoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
