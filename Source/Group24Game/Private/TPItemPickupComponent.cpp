#include "TPItemPickupComponent.h"

#include "Group24Game/Group24GameGameMode.h"

void UTPItemPickupComponent::AddItem(AGroup24GameCharacter* TargetCharacter) const
{
	AGroup24GameGameMode* GameMode = static_cast<AGroup24GameGameMode*>(GetWorld()->GetAuthGameMode());

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Picked up Item " + Item.Name);
	GameMode->CurrentInventory.Add(Item);
	GetOwner()->Destroy();
}
