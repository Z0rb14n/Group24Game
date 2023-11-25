// Copyright Epic Games, Inc. All Rights Reserved.


#include "Group24GamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Group24GameCharacter.h"
#include "Runtime/UMG/Public/UMG.h"

void AGroup24GamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	// yes, because although this is deprecated *apparently* the new version is bork??
	InputComponent->BindAction("TEST_OpenUI", IE_Pressed, this, &AGroup24GamePlayerController::OnAttemptTestUIOpen);
}

void AGroup24GamePlayerController::OnAttemptTestUIOpen()
{
	if (ensure(WidgetTemplate))
	{
		if (!WidgetInstance)
		{
			WidgetInstance = static_cast<UTestUIWidget*>(CreateWidget(this, WidgetTemplate));
		}
	}
	if (ensure(WidgetInstance))
	{
		if (!WidgetInstance->IsInViewport())
		{
			WidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			static_cast<AGroup24GameCharacter*>(GetCharacter())->SetIsMovementEnabled(false);
		} else
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
			bShowMouseCursor = false;
			static_cast<AGroup24GameCharacter*>(GetCharacter())->SetIsMovementEnabled(true);
			// seems like it permanently softlocks the editor until you do this bs:
			// https://forums.unrealengine.com/t/c-create-widget/298562/3
			FSlateApplication::Get().SetAllUserFocusToGameViewport();
		}
	}
}