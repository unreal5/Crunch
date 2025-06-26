#pragma once
#include "CoreMinimal.h"
#include "CGameplayAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class ECAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	BasicAttack UMETA(DisplayName = "Basic Attack"),
	Ability1 UMETA(DisplayName = "Ability 1"),
	Ability2 UMETA(DisplayName = "Ability 2"),
	Ability3 UMETA(DisplayName = "Ability 3"),
	Ability4 UMETA(DisplayName = "Ability 4"),
	Ability5 UMETA(DisplayName = "Ability 5"),
	Ability6 UMETA(DisplayName = "Ability 6"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
};