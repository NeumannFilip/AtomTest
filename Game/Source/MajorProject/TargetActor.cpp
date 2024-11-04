#include "TargetActor.h"

void UTargetActor::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void UTargetActor::SetTarget(const TArray<AActor*>& Actors)
{
	SetTargetActor(Actors.IsValidIndex(0) ? Actors[0] : nullptr);
}

AActor* UTargetActor::TryGetTargetActor() const
{
	return GetTargetActor();
}

bool UTargetActor::IsTargetSet() const
{
	return !!GetTargetActor();
}

void UTargetActor::ClearAll()
{
	TargetActor = nullptr;
}

void UTargetActor::SetTargetActor(AActor* Actor)
{
	if (Actor != TargetActor)
	{
		TargetActor = Actor;
	}
}

AActor* UTargetActor::GetTargetActor() const
{
	return TargetActor;
}
