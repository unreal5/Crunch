// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SendTargetGroup.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                 const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	if (TargetSocketNames.Num() < 2) return;

	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor) return;
	auto OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
	if (!OwnerASC) return;

	FGameplayEventData Data;
	for (int32 i = 1; i < TargetSocketNames.Num(); ++i)
	{
		FGameplayAbilityTargetData_LocationInfo* LocationInfo = new FGameplayAbilityTargetData_LocationInfo();
		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketNames[i - 1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketNames[i]);
		LocationInfo->SourceLocation.LiteralTransform.SetLocation(StartLoc);
		LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLoc);

		Data.TargetData.Add(LocationInfo);
	}
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, Data);
}
