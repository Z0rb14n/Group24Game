#pragma once

#include "FUInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FUInventoryItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	UTexture2D* IconImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FString Name;

	FUInventoryItem();
};
