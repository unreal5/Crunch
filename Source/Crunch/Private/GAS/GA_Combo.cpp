// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"

#include "CAbilitySystemStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(CAbilitySystemStatics::Ability_BasicAttack);
	BlockAbilitiesWithTag.AddTag(CAbilitySystemStatics::Ability_BasicAttack);
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo,
                                const FGameplayEventData* TriggerEventData)
{
	// 激活技能前，需要检查是否有足够的资源（如能量、冷却时间等）；除此之处，还需要提交（Commit）消耗的资源。
	// CommitAbility 函数会检查技能是否可以被激活，并在成功时（返回true）提交技能的消耗（如冷却时间、能量等）。
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// 重要! 没有成功提交技能（资源不足或其他原因），则结束技能，技能不会自动结束，必须显式调用 EndAbility。
		// 如果没有显式结束技能，会导致该技能持续激活状态。
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

	auto PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, FName("PlayComboMontage"), ComboMontage, 1.0f, FName("ComboFinished"));
	PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
	PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
	PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
	PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);

	PlayComboMontageTask->ReadyForActivation();

	// 给出Tag的父Tag，子类的也符合条件；即等待所有Ability.Combo.Change.*的事件。
	auto WaitForComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, AbilityComboChangeTag, nullptr, false, false);
	WaitForComboChangeEventTask->EventReceived.AddDynamic(this, &UGA_Combo::ComboChangedEventReceived);
	WaitForComboChangeEventTask->ReadyForActivation();

	SetupWaitComboInputPress();
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Payload)
{
	const FGameplayTag EventTag = Payload.EventTag;
	if (EventTag.MatchesTagExact(AbilityComboChangeEndTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("收到结束连招的事件"));
		NextComboName = NAME_None;
		return;
	}
	NextComboName = EventTag.GetTagLeafName();
	UE_LOG(LogTemp, Warning, TEXT("ComboChangedEventReceived: %s"), *NextComboName.ToString());
}

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPressTask->OnPress.AddDynamic(this, &UGA_Combo::HandleInputPress);
	WaitInputPressTask->ReadyForActivation();
}

void UGA_Combo::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

void UGA_Combo::TryCommitCombo()
{
	if (NextComboName == NAME_None) return;

	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (!OwnerAnimInstance) return;

	OwnerAnimInstance->Montage_SetNextSection(OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage), NextComboName,
	                                          ComboMontage);
}
