// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUIWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CheckBox.h"

void UTestUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox && !CheckBox->OnCheckStateChanged.Contains(this, "OnCheckboxChanged"))
	{
		CheckBox->OnCheckStateChanged.AddDynamic(this, &UTestUIWidget::OnCheckboxChanged);
	}
	ensure(QTEWidgetTemplate);
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