#pragma once

#include "BowlComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBowlComponent  : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	//UBowlComponent();

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> WidgetTemplate;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleUI();

private:
	UPROPERTY()
	UUserWidget* WidgetInstance;
		
};
