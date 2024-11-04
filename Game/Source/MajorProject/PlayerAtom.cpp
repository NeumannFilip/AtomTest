#include "PlayerAtom.h"

UPlayerAtom::UPlayerAtom()
{
	bUnique = true;
}

void UPlayerAtom::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerAtom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UAtom* UPlayerAtom::GetRedirectedAtom()
{
	return AtomRedirectors.IsValidIndex(0) ? AtomRedirectors[0] : this;
}

int32 UPlayerAtom::GetAtomIndex() const
{
	return AtomIndex;
}
