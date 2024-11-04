#pragma once
#include "AtomController.h"
#include "CoreMinimal.h"
#include "AtomFunctions.h"
#include "AtomMainController.h"
#include "GameFramework/Actor.h"
#include "AtomPlayerController.generated.h"

class AAtomCursor;
class AAtom;
class UPlayerMappableInputConfig;

UCLASS()
class MAJORPROJECT_API AAtomPlayerController : public AAtomMainController
{
	GENERATED_BODY()
public:

	AAtomPlayerController();
	//Class for spawning alongside the character rest of controllers
	void SpawnControllers();
	
	//overriding classes
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;

	virtual void EnableInput(APlayerController* PlayerController) override;
	virtual void DisableInput(APlayerController* PlayerController) override;

	virtual void SetupPlayerInputMode() override;

	virtual void Serialize(FArchive& Ar) override;

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=bInstant))
	void FocusSelectedCharacter(bool bInstant = false);

	AAtomController* GetAtomController() const;
	
	template <class T>
	T* GetAtomController() const
	{
		return Cast<T>(GetAtomController());
	};

	AAtomCursor* GetCursor() const;
	FAtomSelector* GetSelector();
	
	

	UPROPERTY(EditDefaultsOnly)
	TArray<UPlayerMappableInputConfig*> DefaultInputConfigs;



protected:

	UPROPERTY()
	AAtomController* KeyboardAndMouseController;

	UPROPERTY()
	AAtomController* GamepadController;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AAtomController> KeyboardAndMouseControllerClass;

	FAtomSelector Selector;

private:

	AAtomCursor* SpawnCursor();


	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AAtomCursor> CursorClass;
	
	UPROPERTY(Transient)
	AAtomCursor* Cursor;
};
