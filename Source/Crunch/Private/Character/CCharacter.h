// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Gameplay Ability", meta=(AllowPrivateAccess="true"))
	class UCAbilitySystemComponent* CAbilitySystemComponent;
	UPROPERTY()
	class UCAttributeSet* CAttributeSet;

	/*			UI			*/
	UPROPERTY(VisibleDefaultsOnly, Category="GUI")
	class UWidgetComponent* OverHeadWidgetComponent;

	void ConfigureOverHeadStatusWidget();

	UPROPERTY(EditDefaultsOnly, Category="GUI")
	float HeadStatGaugeVisibilityCheckUpdageGap = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category="GUI")
	float HeadStatGaugeVisibilityRangeSquared = 1000000.0f;
	
	FTimerHandle HeadStatGuageVisibilityUpdateTimerHandle;
	UFUNCTION()
	void UpdateHeadGuageVisibility();
};
