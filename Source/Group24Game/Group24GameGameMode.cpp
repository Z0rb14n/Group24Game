// Copyright Epic Games, Inc. All Rights Reserved.

#include "Group24GameGameMode.h"
#include "Group24GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGroup24GameGameMode::AGroup24GameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
