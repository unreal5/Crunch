// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"

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
