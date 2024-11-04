#include "AtomGameState.h"

#include "Atom.h"

TArray<FName> UAtomManager::GetAtomIds() const
{
	TArray<FName> Ids;
	for (const auto& Atom : Atoms)
	{
		Ids.Add(Atom->GetFName());
	}
	return Ids;
}

AActor* UAtomManager::GetAtom(FGameplayTag AtomId) const
{
	for (const auto* Atom : Atoms)
	{
		if (Atom->GetAtomID() == AtomId)
		{
			return Atom->GetOwner();
		}
	}
	return nullptr;
}

void UAtomManager::GetAtoms(TArray<AActor*>& OutAtoms) const
{
	OutAtoms.Empty(OutAtoms.Num());
	for (const auto* Atom : Atoms)
	{
		OutAtoms.Add(Atom->GetOwner());
	}
}

AAtomGameState::AAtomGameState()
{
	PlayerAtoms = CreateDefaultSubobject<UAtomManager>(TEXT("PlayerAtomManager"));
	EnemyAtoms = CreateDefaultSubobject<UAtomManager>(TEXT("EnemyAtomManager"));
}

void AAtomGameState::RegisterPlayerAtom(UAtom* AtomToRegister)
{
	Atoms.Add(AtomToRegister->GetOwner()->GetFName(),AtomToRegister);
}

void AAtomGameState::UnRegisterPlayerAtom(UAtom* AtomToUnregister)
{
	Atoms.Remove(AtomToUnregister->GetOwner()->GetFName());
}

UAtom* AAtomGameState::GetAtom(FName Id) const
{
	return Atoms.FindRef(Id);
}
