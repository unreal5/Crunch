

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	class UValueGauge* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UValueGauge* ManaBar;

	UPROPERTY()
	class UAbilitySystemComponent* OwnerASC;
};
