// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"

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

	UE_LOG(LogTemp, Warning, TEXT("GA_Combo::ActivateAbility - Ability activated successfully."));
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
