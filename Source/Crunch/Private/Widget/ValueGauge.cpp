// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (ProgressBar)
	{
		ProgressBar->SetFillColorAndOpacity(BarColor);
	}
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;

	if (FMath::IsNearlyZero(NewMaxValue)) return;

	if (!ProgressBar) return;
	if (!ValueText) return;

	float NewPercentage = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercentage);
	FNumberFormattingOptions FormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	ValueText->SetText(FText::Format(FTextFormat::FromString("{0} / {1}"),
	                                 FText::AsNumber(NewValue, &FormattingOptions),
	                                 FText::AsNumber(NewMaxValue, &FormattingOptions)));
}

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute,
                                                 const FGameplayAttribute& MaxAttribute)
{
	if (!ASC) return;
	bool bFound = false;
	float Value = ASC->GetGameplayAttributeValue(Attribute, bFound);
	check(bFound);
	bFound = false;
	float MaxValue = ASC->GetGameplayAttributeValue(MaxAttribute, bFound);
	check(bFound);
	SetValue(Value, MaxValue);

	ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		SetValue(Data.NewValue, CachedMaxValue);
	});
	ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		SetValue(CachedValue, Data.NewValue);
	});
}
