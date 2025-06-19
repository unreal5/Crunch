// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool IsMoving() const { return !IsNotMoving(); }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool IsNotMoving() const { return FMath::IsNearlyZero(Speed); }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetYawSpeed() const { return YawSpeed; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool IsJumping() const { return bIsJumping; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool IsOnGround() const { return !IsJumping(); }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetLookYawOffset() const { return LookRotOffset.Yaw; }

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	float GetLookPitchOffset() const { return LookRotOffset.Pitch; }
	
private:
	UPROPERTY()
	class ACharacter* OwnerCharacter;
	UPROPERTY()
	class UCharacterMovementComponent* OwnerMovementComponent;

	float Speed = 0.0f;
	float YawSpeed = 0.0f;
	float SmoothedYawSpeed = 0.0f;
	bool bIsJumping = false;
	UPROPERTY(EditAnywhere, Category=Animation)
	float YawSpeedSmoothLerpSpeed = 1.0f;
	FRotator BodyPrevRot;
	FRotator LookRotOffset;
};
