#include "AtomPlayerController.h"

#include "AtomCursor.h"

AAtomPlayerController::AAtomPlayerController()
{
}

void AAtomPlayerController::SpawnControllers()
{
	UClass* Class = KeyboardAndMouseControllerClass.LoadSynchronous();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Name = Class->GetFName();
	SpawnParameters.Instigator = GetInstigator();
	KeyboardAndMouseController = GetWorld()->SpawnActor<AAtomController>(Class,SpawnParameters);
	KeyboardAndMouseController->Cursor = Cursor;
	KeyboardAndMouseController->EnableInput(this);
}

void AAtomPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void AAtomPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Cursor = SpawnCursor();
	SpawnControllers();
}

void AAtomPlayerController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(PlayerController);
	if (GetPawn())
	{
		GetPawn()->EnableInput(this);
	}
	if (GetPlayerInputMode() == EPlayerInputMode::KeyboardAndMouse)
		KeyboardAndMouseController->Activate();
	else
		GamepadController->Activate();


	GetCursor()->SetCursorVisibility(true);
}

void AAtomPlayerController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);
	if (GetPawn())
	{
		GetPawn()->DisableInput(this);
	}
	KeyboardAndMouseController->Deactivate();
	GamepadController->Deactivate();

	GetCursor()->SetCursorVisibility(false);
}

void AAtomPlayerController::SetupPlayerInputMode()
{
	Super::SetupPlayerInputMode();
	if(KeyboardAndMouseController && GamepadController)
	{
		if(GetPlayerInputMode() == EPlayerInputMode::KeyboardAndMouse)
		{
			GamepadController->Deactivate();
			KeyboardAndMouseController->Activate();
		}
		else
		{
			KeyboardAndMouseController->Deactivate();
			GamepadController->Activate();
		}
	}
}

void AAtomPlayerController::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void AAtomPlayerController::FocusSelectedCharacter(bool bInstant)
{
	GetAtomController()->FocusSelectedCharacter(false, bInstant);
}

AAtomController* AAtomPlayerController::GetAtomController() const
{
	return GetPlayerInputMode() == EPlayerInputMode::KeyboardAndMouse ? KeyboardAndMouseController : GamepadController;
}

AAtomCursor* AAtomPlayerController::GetCursor() const
{
	return Cursor;
}

FAtomSelector* AAtomPlayerController::GetSelector()
{
	return &Selector;
}

AAtomCursor* AAtomPlayerController::SpawnCursor()
{
	UClass* Class = CursorClass.LoadSynchronous();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Name = Class->GetFName();
	SpawnParameters.Instigator = GetInstigator();
	return GetWorld()->SpawnActor<AAtomCursor>(Class, SpawnParameters);

}
