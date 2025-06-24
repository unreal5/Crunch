// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/OverHeadStatsGauge.h"

// Sets default values
ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("CAbilitySystemComponent"));
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>(TEXT("CAttributeSet"));

	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetComponent"));
	OverHeadWidgetComponent->SetupAttachment(RootComponent);
	OverHeadWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	OverHeadWidgetComponent->SetDrawAtDesiredSize(true);
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	ConfigureOverHeadStatusWidget();
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController()) // AI角色
	{
		ServerSideInit();
	}
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
	CAbilitySystemComponent->GiveInitialAbilities();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

bool ACCharacter::IsLocallyControlledByPlayer() const
{
	AController* PC = GetController();
	return PC && PC->IsLocalPlayerController();
}

void ACCharacter::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent) return;
	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	OverHeadWidgetComponent->SetHiddenInGame(false);

	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (!OverHeadStatsGauge) return;

	OverHeadStatsGauge->ConfigureWithASC(GetAbilitySystemComponent());
	GetWorldTimerManager().ClearTimer(HeadStatGuageVisibilityUpdateTimerHandle);
	GetWorldTimerManager().SetTimer(HeadStatGuageVisibilityUpdateTimerHandle, this,
	                                &ThisClass::UpdateHeadGuageVisibility, HeadStatGaugeVisibilityCheckUpdageGap,
	                                true);
}

void ACCharacter::UpdateHeadGuageVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		float DistSquared = FVector::DistSquared(LocalPlayerPawn->GetActorLocation(), GetActorLocation());

		bool bHiddenInGame = DistSquared > HeadStatGaugeVisibilityRangeSquared;
		OverHeadWidgetComponent->SetHiddenInGame(bHiddenInGame);
	}
}
