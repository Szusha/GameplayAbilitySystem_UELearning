// Coryright Szusha

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	/* Input */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	/* Movement */
	void Move(const struct FInputActionValue& InputActionValue);
	
	/* Trace */
	void CursorTrace();

	TScriptInterface<class IEnemyInterface> LastActor;  // TScriptInterface is a new wrapper for raw Interface pointers
	TScriptInterface<class IEnemyInterface> ThisActor;

};
