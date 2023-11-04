// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUIWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CheckBox.h"

void UTestUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox)
	{
		CheckBox->OnCheckStateChanged.AddDynamic(this, &UTestUIWidget::OnCheckboxChanged);
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
		const FVector2D Pos = CanvasPanelSlot->GetPosition();
		const FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

		if (FVector2D::Distance(Pos, MousePos) <= 200)
		{
			FVector2D Diff = Pos - MousePos;
			Diff.Normalize();
			Diff = Diff * 200;
			FVector2D FinalPos = (Diff + MousePos).ClampAxes(0,1000);
			CanvasPanelSlot->SetPosition(FinalPos);
		}
	}
}