#include "BowlComponent.h"

#include "Blueprint/UserWidget.h"
#include "Group24Game/UIUtils.h"


void UBowlComponent::OpenUI()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attempting to open Bowl UI"));
	if (ensure(WidgetTemplate))
	{
		if (!WidgetInstance)
		{
			WidgetInstance = CreateWidget(UIUtils::PlayerController, WidgetTemplate);
		}
	}
	if (ensure(WidgetInstance))
	{
		if (!WidgetInstance->IsInViewport())
		{
			WidgetInstance->AddToViewport();
			UIUtils::OnOpenUI();
		} else
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
			UIUtils::OnCloseUI();
		}
	}
}
