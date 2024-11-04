#include "AtomLibrary.h"

#include "Atom.h"
#include "AtomGameState.h"
#include "GameplayTagContainer.h"
#include "MajorProjectGameMode.h"
#include "Spawner.h"

AActor* UAtomLibrary::GetPlayerAtom(const UObject* WorldContextObject, FGameplayTag AtomId)
{
	if(const auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if(const auto* AtomGameState = World->GetGameState<AAtomGameState>())
		{
			return AtomGameState->PlayerAtoms->GetAtom(AtomId);
		}
	}
	return nullptr;
}

void UAtomLibrary::GetPlayerTeam(const UObject* WorldContextObject, TArray<AActor*>& Team)
{
	if(const auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if(const auto* AtomGameState = World->GetGameState<AAtomGameState>())
		{
			return AtomGameState->PlayerAtoms->GetAtoms(Team);
		}
	}
}

AActor* UAtomLibrary::SpawnPlayerAtom(const UObject* WorldContextObject, TSubclassOf<AActor> Class,
                                      AActor* DestinationActor)
{
	if(const auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if(auto* AtomGameMode = World->GetAuthGameMode<AMajorProjectGameMode>())
		{
			if(auto* Atom = AtomGameMode->SpawnAtom(Class, DestinationActor->GetTransform()))
			{
				AtomGameMode->GetGameState<AAtomGameState>()->RegisterPlayerAtom(Atom);
				return Atom->GetOwner();
			}
		}
	}
	return nullptr;
}

void UAtomLibrary::SpawnAtomsFromSpawners(const TArray<ASpawner*> Spawners)
{
	for( auto* Spawner : Spawners)
	{
		if(Spawner->GetSpawnedAtom() == nullptr)
		{
			Spawner->SpawnAtom();
		}
	}
}
