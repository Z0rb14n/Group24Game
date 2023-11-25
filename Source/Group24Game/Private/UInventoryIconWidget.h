#pragma once

#include "CoreMinimal.h"
#include "FUInventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "UInventoryIconWidget.generated.h"

UCLASS(Abstract)
class UInventoryIconWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NameDisplay;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* IconImage;

	UFUNCTION(BlueprintCallable)
	void SetDisplayedObject(FUInventoryItem Item);
};
