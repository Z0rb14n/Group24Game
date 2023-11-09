// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Private/TestUIWidget.h"
#include "GameFramework/PlayerController.h"
#include "Group24GamePlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class GROUP24GAME_API AGroup24GamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UTestUIWidget> WidgetTemplate;
	
	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	void OnAttemptTestUIOpen();
	// End Actor interface
private:
	UPROPERTY()
	UTestUIWidget* WidgetInstance;
};
