#include "CPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ACPlayerCharacter::ACPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator{0.f, 720.f, 0.f};
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (auto OwningPlayerController = GetController<APlayerController>())
	{
		auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			OwningPlayerController->GetLocalPlayer());
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* IC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	IC->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	IC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);
	IC->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleMoveInput);

	// 绑定游戏能力输入
	// Lambda表达式第一个参数似乎必须是const FInputActionValue&，待确认。
	auto InputExpression = [this](const FInputActionValue& InputActionValue, ECAbilityInputID InputID)
	{
		auto GAS = GetAbilitySystemComponent();
		if (!GAS) return;

		int32 InputIDValue = static_cast<int32>(InputID);
		const bool bIsPressed = InputActionValue.Get<bool>();
		bIsPressed ? GAS->AbilityLocalInputPressed(InputIDValue) : GAS->AbilityLocalInputReleased(InputIDValue);
	};
	for (auto& [InputID, InputAction] : GameplayAbilityInputActions)
	{
		if (InputAction)
		{
			IC->BindActionValueLambda(InputAction, ETriggerEvent::Triggered, InputExpression, InputID);
		}
	}
}

void ACPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ACPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D InputValue = InputActionValue.Get<FVector2D>();
	if (InputValue.IsNearlyZero())
		return;
	FRotator Rotator{0.f, GetControlRotation().Yaw, 0.f};
	FVector MoveDirecton{InputValue.Y, InputValue.X, 0.f};
	MoveDirecton = Rotator.RotateVector(MoveDirecton);
	AddMovementInput(MoveDirecton);
}
