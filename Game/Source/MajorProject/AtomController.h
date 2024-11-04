// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AtomController.generated.h"


class AAtomCursor;
struct FAtomSelector;
class UAtom;
class APlayerController;
class UPlayerAtom;
class UInputAction;
class UAbility;

//Gamepad??????
//would be nice to add it to make it even more expandable
// if gamepad add delegate to handle input switch

UCLASS(NotPlaceable)
class MAJORPROJECT_API AAtomController : public AActor
{
	GENERATED_BODY()
	
public:
	//The ideas is to have controller take care of inputs potentially abilities as well
	//so if I populate Keyboard and mouse controller to bind inputs I can potentially call them here
	//example would be cancel actions, cycle character input etc.

	AAtomController();

	UFUNCTION(BlueprintPure)
	bool IsActive() const { return bActive; }
	
	virtual void Tick(float DeltaTime) override;


	virtual void OnSelectionChanged();
	
	//
	virtual void Activate();
	virtual void Deactivate();
	
	virtual void BindInputActions();

	//Input
	virtual void EnableInput(APlayerController* PlayerController) override;
	virtual void DisableInput(APlayerController* PlayerController) override;
	virtual bool IsInputEnabled() const;

	UPROPERTY(Transient)
	bool bInputEnabled;

	const TArray<UAtom*>& GetSelectedAtoms()const;
	const UAtom* GetFirstSelectedAtom()const;
	void SetSelectedAtom(UAtom* Atom);
	//other cases with multiple atoms or selecting atoms from ui like from hero icon.

	FAtomSelector* Selector;

	/* Gets the controller that owns the component, this will always be valid during gameplay but can return null in the editor */
	template <class T>
	T* GetController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' template parameter to GetController must be derived from AController");
		return Cast<T>(GetOwner());
	}

	void FocusSelectedCharacter(bool bResetCamera = false, bool bInstant = false);

	UPROPERTY(Transient)
	AAtomCursor* Cursor;

	//////
	///
	///This Class potentially could handle abilities themselves if there were more.

	//too make it fun
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TArray<class UPlayerMappableInputConfig*> ControllerSpecificInputConfigs;
	
private:

	UPROPERTY()
	bool bActive;

	UPROPERTY()
	bool bActionsBound;
protected:
	virtual void BeginPlay() override;
	virtual void Init();
	virtual void SetupPlayerInputMode();
	
	UPROPERTY()
	TArray<UAbility*> Abilities;
	
};
