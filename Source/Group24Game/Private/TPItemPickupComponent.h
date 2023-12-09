#pragma once
#include "FUInventoryItem.h"
#include "Group24Game/Group24GameCharacter.h"

#include "TPItemPickupComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UTPItemPickupComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FUInventoryItem Item;
	
	UFUNCTION(BlueprintCallable)
	void AddItem(AGroup24GameCharacter* TargetCharacter) const;
};
