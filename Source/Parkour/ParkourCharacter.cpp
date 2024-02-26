#include "ParkourCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AParkourCharacter::AParkourCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AParkourCharacter::BeginPlay()
{
	 

	Super::BeginPlay();


	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

}

void AParkourCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParkourCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AParkourCharacter::Move);

		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AParkourCharacter::Look);

		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AParkourCharacter::Jump);
	
	}
}

void AParkourCharacter::Move(const FInputActionValue &InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}

}

void AParkourCharacter::Look(const FInputActionValue &InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if(IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AParkourCharacter::Jump()
{
	ACharacter::Jump();
}
