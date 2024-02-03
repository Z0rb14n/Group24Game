#include "DrugMakingUIWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

void UDrugMakingUIWidget::NativeConstruct()
{
}

void UDrugMakingUIWidget::AddIngredient(const int IngredientID)
{
	if (AddedIngredients.Contains(IngredientID))
		AddedIngredients.Add(IngredientID, AddedIngredients[IngredientID]+1);
	else
		AddedIngredients.Add(IngredientID, 1);
	BowlImage->SetBrushFromTexture(NormalBowl);
}

void UDrugMakingUIWidget::MixStart()
{
	GetWorld()->GetTimerManager().SetTimer(MixTimerHandle, this, &UDrugMakingUIWidget::OnMixFinish, MixTime, false);
	BowlImage->SetBrushFromTexture(CoveredBowl);
	MixButton->SetIsEnabled(false);
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Mixing"));
}

void UDrugMakingUIWidget::OnMixFinish()
{
	const bool MixSuccess = Mix();
	BowlImage->SetBrushFromTexture(MixSuccess ? GreenBowl : RedBowl);
	MixButton->SetIsEnabled(true);
}


bool UDrugMakingUIWidget::Mix()
{
	const int* AmmoniaCount = AddedIngredients.Find(1);
	const int* BleachCount = AddedIngredients.Find(2);
	const bool Success = AmmoniaCount != nullptr && *AmmoniaCount > 0 && BleachCount != nullptr && *BleachCount > 0;
	AddedIngredients.Reset();
	if (Success)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("now ur dead"));
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("who let you cook"));
	}
	return Success;
}
