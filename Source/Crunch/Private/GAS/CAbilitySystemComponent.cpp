// Fill out your copyright notice in the Description page of Project Settings.


#include "CAbilitySystemComponent.h"



void UCAbilitySystemComponent::ApplyInitialEffects()
{
	// 只在服务器上应用初始效果
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;


	for (TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		FGameplayEffectContextHandle EffectContext = MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
	}
}

void UCAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	for (TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		if (AbilityClass)
		{
			GiveAbility(FGameplayAbilitySpec(AbilityClass, 0.0f, INDEX_NONE, nullptr));
		}
	}

	for (TSubclassOf<UGameplayAbility>& AbilityClass : BasicAbilities)
	{
		if (AbilityClass)
		{
			GiveAbility(FGameplayAbilitySpec(AbilityClass, 1.0f, INDEX_NONE, nullptr));
		}
	}
}
