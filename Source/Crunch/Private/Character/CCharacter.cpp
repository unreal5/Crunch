// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"

// Sets default values
ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("CAbilitySystemComponent"));
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>(TEXT("CAttributeSet"));
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}
