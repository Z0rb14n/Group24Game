#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DrugMakingUIWidget.generated.h"

UCLASS(Abstract)
class UDrugMakingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void AddIngredient(const int IngredientID);
	UFUNCTION(BlueprintCallable)
	void MixStart();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* NormalBowl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CoveredBowl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RedBowl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* GreenBowl;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* BowlImage;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* MixButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MixTime = 2;
private:
	TMap<int, int> AddedIngredients;
	FTimerHandle MixTimerHandle;

	void OnMixFinish();
	bool Mix();
};
