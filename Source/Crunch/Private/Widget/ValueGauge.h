// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

struct FGameplayAttribute;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CRUNCH_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetValue(float NewValue, float NewMaxValue);
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
protected:
	virtual void NativePreConstruct() override;

private:
	float CachedValue = 0.0f;
	float CachedMaxValue = 0.0f;
	UPROPERTY(EditAnywhere, Category="Visual")
	FLinearColor BarColor;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UProgressBar* ProgressBar;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* ValueText;
};
