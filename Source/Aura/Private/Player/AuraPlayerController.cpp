// Coryright Szusha


#include "Player/AuraPlayerController.h"
#include "Interaction/EnemyInterface.h"

#include "EnhancedInputSubsystems.h" // input
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Sybsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Sybsystem);
	Sybsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/*
	* Line trace from cursor. There are several scenarios:
	* A. LastActor = nullptr && ThisActor = nullptr
	*    - Do nothing
	* B. LastActor = nullptr && ThisActor is valid:
	*    - Highlight ThisActor
	* C. LastActor is valid && ThisActor = nullptr
	*    - UnHighlight LastActor
	* D. Both are valid, but LastActor != ThisActor
	*    - UnHighlight LastActor && Highlight ThisActor
	* E. Both are valid, LastActor = ThisActor
	*    - Do nothing
	*/

	if (LastActor == nullptr)  // Case A will occur automatically if ThisActor is nullptr -> Do nothing.
	{
		if (ThisActor != nullptr)  // Case B
		{
			ThisActor->HighlightActor();
		}

	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)  // Case C
		{
			LastActor->UnHighlightActor();
		}
		else // both Actors are valid, Case E will occur automatically LastActor = ThisActor -> Do nothing
		{
			if (LastActor != ThisActor) // Case D
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}

}
