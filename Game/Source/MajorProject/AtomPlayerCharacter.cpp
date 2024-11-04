#include "AtomPlayerCharacter.h"

#include "AtomController.h"


AAtomPlayerCharacter::AAtomPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AAtomPlayerCharacter::SpawnController()
{

}

void AAtomPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAtomPlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAtomPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAtomPlayerCharacter::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}