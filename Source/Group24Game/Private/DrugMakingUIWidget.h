#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DrugMakingUIWidget.generated.h"

UCLASS(Abstract)
class UDrugMakingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void AddIngredient(const int id);
	UFUNCTION(BlueprintCallable)
	bool Mix();
private:
	int Data;
};
