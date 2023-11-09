// Fill out your copyright notice in the Description page of Project Settings.

#include "QTEDisplayWidget.h"

#include "Components/TextBlock.h"
#include "Runtime/Core/Public/Containers/StringConv.h"

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
	FailDisplay->SetRenderOpacity(bNewFailed ? 0.5f : 0);
}
