// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OverHeadStatsGauge.h"

#include "ValueGauge.h"
#include "GAS/CAttributeSet.h"

void UOverHeadStatsGauge::ConfigureWithASC(UAbilitySystemComponent* ASC)
{
	if (!ASC) return;
	
	if (HealthBar) HealthBar->SetAndBoundToGameplayAttribute(ASC, UCAttributeSet::GetHealthAttribute(),
	                                                         UCAttributeSet::GetMaxHealthAttribute());
	if (ManaBar) ManaBar->SetAndBoundToGameplayAttribute(ASC, UCAttributeSet::GetManaAttribute(),
	                                                     UCAttributeSet::GetMaxManaAttribute());
}
