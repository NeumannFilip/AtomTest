// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomController.h"

#include "Atom.h"
#include "AtomCamera.h"
#include "AtomGameState.h"
#include "AtomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerAtom.h"

// Sets default values
AAtomController::AAtomController()
{
	
}

// Called when the game starts or when spawned
void AAtomController::BeginPlay()
{
	Super::BeginPlay();
	Selector = GetController<AAtomPlayerController>()->GetSelector();
	if(const auto* GameState = GetWorld()->GetGameState<AAtomGameState>())
	{
		if(GameState->PlayerAtoms->Atoms.IsEmpty() ==false)
		{
			if(Selector->GetFirstSelected()==nullptr)
			{
				GameState->PlayerAtoms->Atoms[0]->GetOwner()->DispatchBeginPlay();
				Selector->Select(GameState->PlayerAtoms->Atoms[0]);
			}
			Selector->OnSelectionChanged.AddUObject(this, &AAtomController::OnSelectionChanged);
			OnSelectionChanged();
		}
	}
}

void AAtomController::Init()
{
	if(auto* Camera = GetController<APlayerController>()->GetPawn<AAtomCamera>())
		Camera->FocusOnActor(Selector->GetFirstSelected()->GetOwner());
}

void AAtomController::SetupPlayerInputMode()
{
}


// Called every frame
void AAtomController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtomController::OnSelectionChanged()
{
}

void AAtomController::Activate()
{
	bActive = true;
	EnableInput(GetController<APlayerController>());
	SetActorTickEnabled(true);
}

void AAtomController::Deactivate()
{
	DisableInput(GetController<APlayerController>());
	SetActorTickEnabled(false);
	bActive = false;
}

void AAtomController::BindInputActions()
{
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		
	}
}

void AAtomController::EnableInput(APlayerController* PlayerController)
{
	Super::EnableInput(PlayerController);
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		for (const auto* InputConfig : ControllerSpecificInputConfigs)
		{
			InputSubsystem->AddPlayerMappableConfig(InputConfig);
		}
	}
	if (!bActionsBound)
	{
		BindInputActions();
	}
	bInputEnabled = true;
}

void AAtomController::DisableInput(APlayerController* PlayerController)
{
	Super::DisableInput(PlayerController);
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		for (const auto* InputConfig : ControllerSpecificInputConfigs)
		{
			InputSubsystem->RemovePlayerMappableConfig(InputConfig);
		}
	}
	bInputEnabled = false;
}

bool AAtomController::IsInputEnabled() const
{
	return bInputEnabled;
}

const TArray<UAtom*>& AAtomController::GetSelectedAtoms() const
{
	return Selector->GetSelected();
}

const UAtom* AAtomController::GetFirstSelectedAtom() const
{
	return Selector->GetFirstSelected();
}

void AAtomController::SetSelectedAtom(UAtom* Atom)
{
	if(UPlayerAtom* PlayerAtom = Cast<UPlayerAtom>(Atom))
	{
		Atom = PlayerAtom->GetRedirectedAtom();
	}
	Selector->Select(Atom);
}

void AAtomController::FocusSelectedCharacter(bool bResetCamera, bool bInstant)
{
	if(auto* Camera = GetController<APlayerController>()->GetPawn<AAtomCamera>())
	{
		Camera->FocusOnActor(Selector->GetFirstSelected()->GetOwner(), bInstant);
		if(bResetCamera)
		{
			Camera->ResetRotationToDefault();
			Camera->ResetZoomToDefault();
		}
	}
}
