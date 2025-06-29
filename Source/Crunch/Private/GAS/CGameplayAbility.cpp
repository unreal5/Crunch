// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameplayAbility.h"

UAnimInstance* UCGameplayAbility::GetOwnerAnimInstance() const
{
	if (auto OwnerSkeletalMeshComp = GetOwningComponentFromActorInfo()->GetOwner()->FindComponentByClass<USkeletalMeshComponent>()) {
		return OwnerSkeletalMeshComp->GetAnimInstance();
	}
	return nullptr;
}
