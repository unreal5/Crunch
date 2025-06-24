// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "CAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void ApplyInitialEffects();
	void GiveInitialAbilities();
private:
	UPROPERTY(EditDefaultsOnly, Category="GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category="GameplayAbilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	UPROPERTY(EditDefaultsOnly, Category="GameplayAbilities")
	TArray<TSubclassOf<UGameplayAbility>> BasicAbilities;
};
