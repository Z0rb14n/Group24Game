#include "UInventoryIconWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryIconWidget::SetDisplayedObject(const FUInventoryItem Item)
{
	NameDisplay->SetText(FText::FromString(Item.Name));
	IconImage->SetBrushFromTexture(Item.IconImage);
}
