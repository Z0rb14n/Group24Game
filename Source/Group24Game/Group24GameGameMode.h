// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Private/FUInventoryItem.h"
#include "Group24GameGameMode.generated.h"

UCLASS(minimalapi)
class AGroup24GameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGroup24GameGameMode();

	TArray<FUInventoryItem> CurrentInventory;
};



