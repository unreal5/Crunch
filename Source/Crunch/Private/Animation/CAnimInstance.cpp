// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimInstance::NativeInitializeAnimation()
{
	OwnerCharacter = Cast<ACharacter>(GetOwningActor());
	OwnerMovementComponent = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;
}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCharacter || !OwnerMovementComponent)
	{
		return;
	}
	Speed = OwnerMovementComponent->Velocity.Size2D();
	auto BodyRot = OwnerCharacter->GetActorRotation();
	auto BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
	BodyPrevRot = BodyRot;

	YawSpeed = UKismetMathLibrary::SafeDivide(BodyRotDelta.Yaw, DeltaSeconds);
	YawSpeed = FMath::Clamp(YawSpeed, -90.0f, 90.0f);
	SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);

	FRotator CtrlRot = OwnerCharacter->GetBaseAimRotation();
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(CtrlRot, BodyRot);
	
	
	bIsJumping = OwnerMovementComponent->IsFalling();
}
