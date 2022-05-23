// Copyright Epic Games, Inc. All Rights Reserved.

#include "MuliplayerTutorialGameMode.h"
#include "MuliplayerTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMuliplayerTutorialGameMode::AMuliplayerTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
