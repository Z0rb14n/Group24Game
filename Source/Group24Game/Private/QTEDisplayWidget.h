// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QTEDisplayWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UQTEDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* FailDisplay;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* KeyDisplay;
	
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	float TimeSinceStart = 0;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPosition(FVector2D NewPos);
	/**
	 * Yes, you may be wondering, "Jon, why the f--- is there an int here?"
	 *
	 * Well, TCHAR results in a compile error and for some god forsaken reason char and wchar_t also does as well,
	 * TChar needs a size type, uint16 isn't supported by blueprint so f--- unreal, i'm using an int
	 * @param NewKey ANSI character encoding of the key (char) key
	 */
	UFUNCTION(BlueprintCallable)
	void SetDisplayedKey(int NewKey) const;
	
	UFUNCTION(BlueprintCallable)
	int GetDisplayedKey() const;
	
	UFUNCTION(BlueprintCallable)
	void SetHasFailed(bool bNewFailed) const;

	UFUNCTION(BlueprintCallable)
	bool GetHasFailed() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float TimeToFail = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float TimeToDestroy = 1;
};
