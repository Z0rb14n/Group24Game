// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUIWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CheckBox.h"
#include "Components/VerticalBox.h"
#include "UInventoryIconWidget.h"
#include "Group24Game/Group24GameGameMode.h"

void UTestUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox && !CheckBox->OnCheckStateChanged.Contains(this, "OnCheckboxChanged"))
	{
		CheckBox->OnCheckStateChanged.AddDynamic(this, &UTestUIWidget::OnCheckboxChanged);
	}
	ensure(QTEWidgetTemplate);
	if (ensure(InventoryWidgetTemplate))
	{
		TArray<FUInventoryItem> Inv = static_cast<AGroup24GameGameMode*>(GetWorld()->GetAuthGameMode())->CurrentInventory;
		const int Len = Inv.Num();
		while (InventoryBox->GetChildrenCount() > Len)
		{
			InventoryBox->GetChildAt(Len)->RemoveFromParent();
		}
		while (InventoryBox->GetChildrenCount() < Len)
		{
			UInventoryIconWidget* InvWidget = static_cast<UInventoryIconWidget*>(CreateWidget(GetOwningPlayer(), InventoryWidgetTemplate));
			InventoryBox->AddChildToVerticalBox(InvWidget);
		}
		for (int i = 0 ; i < Inv.Num(); ++i)
		{
			FUInventoryItem Item = Inv[i];
			static_cast<UInventoryIconWidget*>(InventoryBox->GetChildAt(i))->SetDisplayedObject(Item);
		}
	}
}

void UTestUIWidget::OnCheckboxChanged(bool bIsChecked)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("not a robot."));
}

void UTestUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CheckBox->IsChecked())
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CheckBox);
		const FVector2D Size = CanvasPanelSlot->GetSize();
		const FVector2D Pos = CanvasPanelSlot->GetPosition();
		const FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		const FVector2D ScreenSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
		if (FVector2D::Distance(Pos, MousePos) <= 200)
		{
			FVector2D Diff = Pos - MousePos;
			Diff.Normalize();
			Diff = Diff * 200;
			FVector2D FinalPos = Diff + MousePos;
			if (FinalPos.X < Size.X) FinalPos.X = Size.X;
			if (FinalPos.X > ScreenSize.X-Size.X/2) FinalPos.X = ScreenSize.X-Size.X/2;
			if (FinalPos.Y < 0) FinalPos.Y = 0;
			if (FinalPos.Y > ScreenSize.Y) FinalPos.Y = ScreenSize.Y;
			CanvasPanelSlot->SetPosition(FinalPos);
		}
	}
	TimeSinceCreation += InDeltaTime;
	if (TimeSinceCreation > 2)
	{
		if (QTEWidgetInstance && QTEWidgetInstance->IsInViewport())
		{
			QTEWidgetInstance->RemoveFromParent();
			QTEWidgetInstance = nullptr;
		}
		if (ensure(QTEWidgetTemplate))
		{
			QTEWidgetInstance = static_cast<UQTEDisplayWidget*>(CreateWidget(GetOwningPlayer(), QTEWidgetTemplate));
			QTEWidgetInstance->SetPosition(FVector2D(FMath::RandRange(150,950),FMath::RandRange(150,950)));
			QTEWidgetInstance->SetDisplayedKey(FMath::RandRange('A','Z'));
			QTEWidgetInstance->AddToViewport();
		}
		TimeSinceCreation = 0;
	}
}