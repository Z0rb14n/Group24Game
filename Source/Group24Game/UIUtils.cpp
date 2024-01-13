#include "UIUtils.h"

#include "EngineUtils.h"
#include "Group24Game/Group24GameCharacter.h"

void UIUtils::EnsurePlayerController()
{
	if (!ensure(PlayerController))
	{
		for (TActorIterator<AGroup24GameCharacter> It(GEngine->GameViewport->GetWorld()); It; ++It)
		{
			const AGroup24GameCharacter* MainActor = *It;
			PlayerController = (AGroup24GamePlayerController*) MainActor->GetController();
			break;
		}
	}
}


void UIUtils::OnOpenUI()
{
	EnsurePlayerController();
	if (ensure(PlayerController))
	{
		PlayerController->bShowMouseCursor = true;
		AGroup24GameCharacter* MainCharacter = (AGroup24GameCharacter*) PlayerController->GetCharacter();
		MainCharacter->SetIsMovementEnabled(false);
	}
}

void UIUtils::OnCloseUI()
{
	EnsurePlayerController();
	if (ensure(PlayerController))
	{
		PlayerController->bShowMouseCursor = false;
		AGroup24GameCharacter* MainCharacter = (AGroup24GameCharacter*) PlayerController->GetCharacter();
		MainCharacter->SetIsMovementEnabled(true);
	}
	// seems like it permanently softlocks the editor until you do this bs:
	// https://forums.unrealengine.com/t/c-create-widget/298562/3
	FSlateApplication::Get().SetAllUserFocusToGameViewport();
}
