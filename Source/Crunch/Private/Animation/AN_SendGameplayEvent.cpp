// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor) return;

	auto OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);
	if (!OwnerASC) return;

	FGameplayEventData EventData;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, EventData);
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (EventTag.IsValid())
		return EventTag.GetTagLeafName().ToString();

	return Super::GetNotifyName_Implementation();
}
