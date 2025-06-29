// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAbilitySystemStatics.h"
#include "CGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Combo : public UCGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Combo();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Ability | Combo | Tags")
	FGameplayTag AbilityComboChangeTag = FGameplayTag::RequestGameplayTag(FName("Ability.Combo.Change"));
	UPROPERTY(EditDefaultsOnly, Category="Ability | Combo | Tags")
	FGameplayTag AbilityComboChangeEndTag = CAbilitySystemStatics::Ability_Combo_Change_End;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;

	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);

	void SetupWaitComboInputPress();
	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	void TryCommitCombo();

	FName NextComboName;
};
