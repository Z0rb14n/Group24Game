// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QTEDisplayWidget.h"
#include "Blueprint/UserWidget.h"
#include "TestUIWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UTestUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UQTEDisplayWidget> QTEWidgetTemplate;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UCheckBox* CheckBox;

private:
	UFUNCTION()
	void OnCheckboxChanged(bool bIsChecked);
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	UPROPERTY()
	UQTEDisplayWidget* QTEWidgetInstance;

	float TimeSinceCreation;
};
