#include "TargetingMode.h"

#include "Target.h"
#include "GameFramework/Character.h"

void UTargetingMode::Initialize(UClass* InTargetClass)
{
	TargetClass = InTargetClass;
	InitializeTargetingModeImplementation();
}

/*bool UTargetingMode::IsActorValidForTarget(const AActor* Actor) const
{
	return IsActorValidForTarget(Actor);
}*/


FVector UTargetingMode::GetTargetLocationForActor(const AActor* Actor) const
{
	
		return Actor->GetActorLocation();
	
}

void UTargetingMode::SetPreviewTarget(AActor* Actor)
{
	SetPreviewTarget(TArray{Actor});
}

void UTargetingMode::SetPreviewTarget(const TArray<AActor*>& Actors)
{
	GetPreviewTarget()->SetTarget(Actors);
}

UTarget* UTargetingMode::GetPreviewTarget() const
{
	if(!PreviewTarget)
	{
		UTargetingMode* This = const_cast<UTargetingMode*>(this);
		This->PreviewTarget = NewObject<UTarget>(This, TargetClass);
	}
	return PreviewTarget;
}

UTarget* UTargetingMode::CollectPreviewTarget()
{
	UTarget* RetPtr = GetPreviewTarget();
	PreviewTarget = nullptr;
	return RetPtr;
}
