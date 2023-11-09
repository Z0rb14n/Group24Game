// Fill out your copyright notice in the Description page of Project Settings.

#include "QTEDisplayWidget.h"

#include "Components/TextBlock.h"
#include "Runtime/Core/Public/Containers/StringConv.h"

void UQTEDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// todo randomize
	SetPosition(FVector2D(200,200));
}

void UQTEDisplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	TimeSinceStart += InDeltaTime;
	if (TimeSinceStart >= TimeToFail + TimeToDestroy)
	{
		if (IsInViewport()) RemoveFromParent();
	} else if (TimeSinceStart >= TimeToFail)
	{
		SetHasFailed(true);
	} else
	{
		if (ensure(GetOwningPlayer()))
		{
			FString wtf = FString() + (char) GetDisplayedKey();
			if (GetOwningPlayer()->WasInputKeyJustPressed(FKey(TCHAR_TO_ANSI(*wtf))))
			{
				if (IsInViewport()) RemoveFromParent();
			}
		}
	}
}

void UQTEDisplayWidget::SetPosition(const FVector2D NewPos)
{
	SetRenderTranslation(NewPos);
}

void UQTEDisplayWidget::SetDisplayedKey(const int NewKey) const
{
	KeyDisplay->SetText(FText::FromString(FString("[") + (char) NewKey + "]"));
}

int UQTEDisplayWidget::GetDisplayedKey() const
{
	return KeyDisplay->GetText().ToString()[1];
}

bool UQTEDisplayWidget::GetHasFailed() const
{
	return FailDisplay->GetRenderOpacity() == 0.5f;
}

void UQTEDisplayWidget::SetHasFailed(const bool bNewFailed) const
{
	FailDisplay->SetOpacity(bNewFailed ? 0.5f : 0);
}
