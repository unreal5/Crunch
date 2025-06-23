#include "GameplayWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ValueGauge.h"
#include "GAS/CAttributeSet.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (!OwnerASC) return;
	if (HealthBar) HealthBar->SetAndBoundToGameplayAttribute(OwnerASC, UCAttributeSet::GetHealthAttribute(),
	                                                         UCAttributeSet::GetMaxHealthAttribute());
	if (ManaBar) ManaBar->SetAndBoundToGameplayAttribute(OwnerASC, UCAttributeSet::GetManaAttribute(),
	                                                       UCAttributeSet::GetMaxManaAttribute());
}
