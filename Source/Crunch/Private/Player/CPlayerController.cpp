// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "CPlayerCharacter.h"

void ACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	CPlayerCharacter = Cast<ACPlayerCharacter>(aPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ServerSideInit();
	}
}

void ACPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	CPlayerCharacter = Cast<ACPlayerCharacter>(P);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ClientSideInit();
	}
}
