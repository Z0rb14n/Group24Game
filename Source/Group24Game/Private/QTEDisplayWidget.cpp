// Fill out your copyright notice in the Description page of Project Settings.

#include "QTEDisplayWidget.h"

#include "Components/TextBlock.h"
#include "Runtime/Core/Public/Containers/StringConv.h"

void UQTEDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UQTEDisplayWidget::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
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
			const FString wtf = FString() + (char) GetDisplayedKey();
			if (GetOwningPlayer()->WasInputKeyJustPressed(FKey(*wtf)))
			{
				if(GEngine)
				{
					const FString Message = TEXT("QTE Success: ") + FString::SanitizeFloat(TimeSinceStart) + " s";
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
				}
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
