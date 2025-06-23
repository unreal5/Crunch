// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "CPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Widget/GameplayWidget.h"

void ACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	CPlayerCharacter = Cast<ACPlayerCharacter>(aPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ServerSideInit();
	}
}

void ACPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget = CreateWidget<UGameplayWidget>(this,GameplayWidgetClass);
	if (!GameplayWidget) return;
	GameplayWidget->AddToViewport();
}

void ACPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	CPlayerCharacter = Cast<ACPlayerCharacter>(P);
	if (!CPlayerCharacter) return;

	CPlayerCharacter->ClientSideInit();
	SpawnGameplayWidget();
}
