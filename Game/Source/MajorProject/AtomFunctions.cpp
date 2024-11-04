#include "AtomFunctions.h"

#include "Atom.h"

void FAtomSelector::Select(UAtom* Atom)
{
	bool bAnyChanged = DeselectAll(Atom);
	if(!SelectedAtoms.Contains(Atom))
	{
		Add_Internal(Atom);
		bAnyChanged = true;
	}
	if(bAnyChanged)
	{
		OnSelectionChanged.Broadcast();
	}
}

void FAtomSelector::Select(const TArray<UAtom*>& Atoms)
{
	bool bAnyChanged = DeselectAll(Atoms);
	for(UAtom* Atom : Atoms)
	{
		if(!SelectedAtoms.Contains(Atom))
		{
			Add_Internal(Atom);
			bAnyChanged = true;
		}
	}
	if(bAnyChanged)
	{
		OnSelectionChanged.Broadcast();
	}
}

bool FAtomSelector::DeselectAll(const TArray<UAtom*> ExceptedAtoms)
{
	bool bAnyChanged = false;
	for (int32 i = SelectedAtoms.Num() - 1; i >= 0; i--)
	{
		if (!ExceptedAtoms.Contains(SelectedAtoms[i]))
		{
			Remove_Internal(SelectedAtoms[i]);
			bAnyChanged = true;
		}
	}
	return bAnyChanged;
}

bool FAtomSelector::DeselectAll(const UAtom* ExceptedAtoms)
{
	bool bAnyChanged = false;
	for (int32 i = SelectedAtoms.Num() - 1; i >= 0; i--)
	{
		if (SelectedAtoms[i] != ExceptedAtoms)
		{
			Remove_Internal(SelectedAtoms[i]);
			bAnyChanged = true;
		}
	}
	return bAnyChanged;
}

UAtom* FAtomSelector::GetFirstSelected() const
{
	return SelectedAtoms.IsValidIndex(0) ? SelectedAtoms[0] : nullptr;
}

const TArray<UAtom*>& FAtomSelector::GetSelected() const
{
	return SelectedAtoms;
}

UAtom* FAtomSelector::GetSelected(int32 Index) const
{
	return SelectedAtoms.IsValidIndex(Index) ? SelectedAtoms[Index] : nullptr;
}

int32 FAtomSelector::GetNumberSelected() const
{
	return SelectedAtoms.Num();
}

void FAtomSelector::Add_Internal(UAtom* Atom)
{
	SelectedAtoms.Remove(Atom);
	Atom->Deselected();
}

void FAtomSelector::Remove_Internal(UAtom* Atom)
{
	SelectedAtoms.Remove(Atom);
	Atom->Deselected();
}
