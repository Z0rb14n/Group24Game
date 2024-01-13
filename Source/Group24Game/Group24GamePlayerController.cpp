// Copyright Epic Games, Inc. All Rights Reserved.


#include "Group24GamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UIUtils.h"
#include "Runtime/UMG/Public/UMG.h"

void AGroup24GamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIUtils::PlayerController = this;

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
			UIUtils::PlayerController = this;
			UIUtils::OnOpenUI();
		} else
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
			UIUtils::PlayerController = this;
			UIUtils::OnCloseUI();
		}
	}
}