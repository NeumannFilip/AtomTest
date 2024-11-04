#include "PlayerSpawner.h"

#include "AtomGameState.h"
#include "MajorProjectGameMode.h"
#include "Components/BillboardComponent.h"
#include "AtomPlayerCharacter.h"
#include "Engine/PlayerStartPIE.h"
#include "Kismet/GameplayStatics.h"

APlayerSpawner::APlayerSpawner()
{
	bAutoSpawn = false;
}

UAtom* APlayerSpawner::SpawnAtom()
{
	if(auto* Atom = Super::SpawnAtom())
	{
		GetWorld()->GetGameState<AAtomGameState>()->RegisterPlayerAtom(Atom);
		return Atom;
	}
	return nullptr;
}

TSubclassOf<AActor> APlayerSpawner::GetClassToSpawn() const
{
	//return Super::GetClassToSpawn();
	return PlayerClass.LoadSynchronous();
}

void APlayerSpawner::PostLoad()
{
	Super::PostLoad();
	if(!AtomsToSpawn.IsEmpty())
	{
		PlayerClass = AtomsToSpawn[0];
		AtomsToSpawn.Empty();
	}
}

FTransform APlayerSpawner::GetSpawnTransform() const
{
	TArray<AActor*> PlayHereActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStartPIE::StaticClass(), PlayHereActors);
	if (PlayHereActors.IsValidIndex(0) && PlayHereActors[0])
	{
		return FTransform(FRotator(0), PlayHereActors[0]->GetActorLocation());
	}
	return Super::GetSpawnTransform();
}
