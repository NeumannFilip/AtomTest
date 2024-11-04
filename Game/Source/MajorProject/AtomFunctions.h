#pragma once

#include "AtomFunctions.generated.h"

class AAtomPlayerCharacter;
class UAtom;

DECLARE_MULTICAST_DELEGATE(FAtomSelectorDelegate);


//Custom class for getting information that can be called from other classes
USTRUCT()
struct MAJORPROJECT_API FAtomSelector
{
	GENERATED_BODY()

	void Select(UAtom* Atom);
	void Select(const TArray<UAtom*>& Atoms);


	/** Returns true if any were deselected */
	bool DeselectAll(const TArray<UAtom*> ExceptedAtoms);
	/** Returns true if any were deselected */
	bool DeselectAll(const UAtom* ExceptedAtoms);
	
	UAtom* GetFirstSelected() const;

	//templates
	template <class T>
	T* GetFirstSelected() const
	{
		return Cast<T>(GetFirstSelected());
	}

	const TArray<UAtom*>& GetSelected() const;

	UAtom* GetSelected(int32 Index) const;

	template <class T>
	T* GetSelected(int32 Index) const
	{
		return SelectedAtoms.IsValidIndex(Index) ? CastChecked<T>(SelectedAtoms[Index]) : nullptr;
	}

	int32 GetNumberSelected() const;

	void Add_Internal(UAtom* Atom);
	void Remove_Internal(UAtom* Atom);
	
	FAtomSelectorDelegate OnSelectionChanged;


	UPROPERTY()
	TArray<UAtom*> SelectedAtoms;
};

//Another struct for more than 1
USTRUCT(BlueprintType)
struct FSquadRecord
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AAtomPlayerCharacter> Class;
	UPROPERTY(EditDefaultsOnly)
	TSet<TSoftClassPtr<class UAbility>> Abilities;
	
};

USTRUCT(BlueprintType)
struct FLevelInfo : public FTableRowBase
{
	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FName> SquadIds;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSquadRecord> Squad;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName NextLevel;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//int32 LevelIndex;
};

UCLASS()
class UAtomFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//idk
public:
	
};
