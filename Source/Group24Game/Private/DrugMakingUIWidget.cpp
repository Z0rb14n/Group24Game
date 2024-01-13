#include "DrugMakingUIWidget.h"

void UDrugMakingUIWidget::NativeConstruct()
{
	Data = 0;
}

void UDrugMakingUIWidget::AddIngredient(const int id)
{
	Data |= id;
}

bool UDrugMakingUIWidget::Mix()
{
	const bool res = Data == 3;
	Data = 0;
	if (res)
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("now ur dead"));
	} else
	{
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("who let you cook"));
	}
	return res;
}
