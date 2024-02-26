#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "ParkourCharacter.h"
#include "GameFramework/PlayerController.h"
#include "PC_Parkour.generated.h"

UCLASS(Abstract)
class APC_Parkour : public APlayerController
{
	GENERATED_BODY()

	
public:


protected:

	
private:
	// Storing a reference to the InputComponent cast to an EnhancedInputComponent
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	void OnPossess(APawn* aPawn);

	// Storing a referencing to pawn
	UPROPERTY()
	AParkourCharacter* PlayerCharacter = nullptr;
	void OnUnPossess();
};
