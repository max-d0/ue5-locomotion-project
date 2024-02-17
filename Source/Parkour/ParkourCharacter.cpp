#include "ParkourCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Set defaults
AParkourCharacter::AParkourCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	// (Test code)
	// Camera->bUsePawnControlRotation = true;
	
	bUseControllerRotationYaw = true;
	// (Test code)
	// GetCharacterMovement()->bOrientRotationToMovement = true;

}

void AParkourCharacter::BeginPlay()
{
	// Call base class  
	Super::BeginPlay();


	// Add input mapping context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add input context
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


		Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AParkourCharacter::StartSprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AParkourCharacter::EndSprint);

		Input->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AParkourCharacter::StartWalk);
		Input->BindAction(WalkAction, ETriggerEvent::Completed, this, &AParkourCharacter::EndWalk);

	}
}

void AParkourCharacter::Move(const FInputActionValue &InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Get direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

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



void AParkourCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AParkourCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}


void AParkourCharacter::StartWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AParkourCharacter::EndWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
