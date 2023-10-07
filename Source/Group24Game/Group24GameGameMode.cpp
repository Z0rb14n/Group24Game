// Copyright Epic Games, Inc. All Rights Reserved.

#include "Group24GameGameMode.h"
#include "Group24GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGroup24GameGameMode::AGroup24GameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
