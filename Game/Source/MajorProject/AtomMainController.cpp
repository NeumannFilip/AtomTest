#include "AtomMainController.h"

void AAtomMainController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

EPlayerInputMode AAtomMainController::GetPlayerInputMode() const
{
	return PlayerInputMode;
}

void AAtomMainController::SetPlayerInputMode(EPlayerInputMode NewMode)
{
	if(PlayerInputMode != NewMode)
	{
		PlayerInputMode = NewMode;
		SetupPlayerInputMode();
	}
}

void AAtomMainController::SetMouseMovementCaptureMode(bool bEnabled)
{
	FInputModeGameOnly GameOnly;
	GameOnly.SetConsumeCaptureMouseDown(!bEnabled);
	SetInputMode(GameOnly);

	SetShowMouseCursor(!bEnabled);
}

void AAtomMainController::RefreshPlayerInputMode()
{
}

void AAtomMainController::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInputMode();
}

void AAtomMainController::SetupPlayerInputMode()
{
	switch(PlayerInputMode)
	{
	case EPlayerInputMode::KeyboardAndMouse:
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);
		}
		break;
	case EPlayerInputMode::Controller:
		{
			const FInputModeGameOnly InputMode;
			SetInputMode(InputMode);
		}
		break;
	}

	SetShowMouseCursor(PlayerInputMode == EPlayerInputMode::KeyboardAndMouse);
}