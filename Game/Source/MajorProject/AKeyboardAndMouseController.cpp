#include "AKeyboardAndMouseController.h"

#include "AtomFunctions.h"
#include "EnhancedInputComponent.h"
#include "Target.h"
#include "TargetingMode.h"

AKeyboardAndMouseController::AKeyboardAndMouseController()
{
}

void AKeyboardAndMouseController::BeginPlay()
{
	Super::BeginPlay();
}

void AKeyboardAndMouseController::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	
}

void AKeyboardAndMouseController::Activate()
{
	Super::Activate();
}

void AKeyboardAndMouseController::Deactivate()
{
	Super::Deactivate();
}

void AKeyboardAndMouseController::BindInputActions()
{
	Super::BindInputActions();
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction,ETriggerEvent::Triggered,this, &ThisClass::ClickTriggered);
	}
}

void AKeyboardAndMouseController::ClickTriggered()
{
	TArray<UAtom*> Atoms = Selector->GetSelected();
	for(int32 i = 0; i< Atoms.Num(); i++)
	{
		UAtom* Atom = Atoms[i];
		UAbility* Ability = Abilities[i];
		const bool bMove = Ability->IsA(UMoveAbility::StaticClass());
		UTargetingMode* TargetingMode = Ability->GetTargetingMode();
		UTarget* Target = TargetingMode->CollectPreviewTarget();
		const bool bPreviewTargetValid = Target->IsTargetSet();

		if(!bMove && bPreviewTargetValid)
		{
			//Atom->OrderMove(Cursor,true);
		}
	}
}
