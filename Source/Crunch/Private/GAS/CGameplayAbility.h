// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility.generated.h"

/**
 * Base class for all gameplay abilities in the Crunch project.
 */
UCLASS()
class CRUNCH_API UCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UAnimInstance* GetOwnerAnimInstance() const;
};
