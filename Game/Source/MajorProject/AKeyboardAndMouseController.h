#pragma once
#include "CoreMinimal.h"
#include "Atom.h"
#include "AtomController.h"
#include "AKeyboardAndMouseController.generated.h"

UCLASS()
class MAJORPROJECT_API AKeyboardAndMouseController : public AAtomController
{
	GENERATED_BODY()

public:

	AKeyboardAndMouseController();

	// Override BeginPlay
	virtual void BeginPlay() override;

	// Override TickComponent
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	virtual void Activate() override;
	virtual void Deactivate() override;

	virtual void BindInputActions() override;


protected:
	//Assignable events
	UFUNCTION(Category=Input)
	void ClickTriggered();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* ClickAction;
};
