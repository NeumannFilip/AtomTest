#include "GroundOnlyTargetingMode.h"

UGroundOnlyTargetingMode::UGroundOnlyTargetingMode()
{
	
}

bool UGroundOnlyTargetingMode::IsActorValidForTargetImplementation(const AActor* Actor) const
{
	return Super::IsActorValidForTargetImplementation(Actor);
}
