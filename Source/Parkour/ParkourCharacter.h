#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ParkourCharacter.generated.h"

UCLASS(config=Game)
class AParkourCharacter : public ACharacter
{
	GENERATED_BODY()

	
protected:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* WalkAction;

public:

	AParkourCharacter();

void NewFunction();

protected:
virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();

	void StartSprint();
	void EndSprint();

	void StartWalk();
	void EndWalk();

	UPROPERTY(EditAnywhere, Category = "Basic Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, Category = "Basic Movement")
	float RunSpeed;
	UPROPERTY(EditAnywhere, Category = "Basic Movement")
	float SprintSpeed;

};

