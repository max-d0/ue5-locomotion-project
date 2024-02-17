#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ParkourCharacter.h"
#include "GameFramework/PlayerController.h"
#include "PC_Parkour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class APC_Parkour : public APlayerController
{
	GENERATED_BODY()

	
public:
	// The Input Action to map to movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	// The Input Action to map to looking around
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;

	// The Input Action to map to jumping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Character Movement")
	UInputAction* ActionJump = nullptr;


protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	// Storing a reference to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	// Storing a referencing to pawn
	UPROPERTY()
	AParkourCharacter* PlayerCharacter = nullptr;
};
