#include "MoveAbility.h"

#include "Atom.h"
#include "GroundOnlyTargetingMode.h"
#include "MoveMarker.h"
#include "TargetActor.h"

UMoveAbility::UMoveAbility()
{
	Name = "Move";
	TargetingModeClass = UGroundOnlyTargetingMode::StaticClass();
	TargetClass = UTargetActor::StaticClass();
	bSignificant = false;
	CastRangeType = EAbilityCastRangeType::Infinite;
}

void UMoveAbility::Serialize(FArchive& Ar)
{
	
	Super::Serialize(Ar);
}

bool UMoveAbility::StartCast(UTarget* InTarget, bool bWithModifier)
{
	
	return Super::StartCast(InTarget, bWithModifier);
}

bool UMoveAbility::IsDirectCast() const
{
	return bDirectCast;	
}

//void UMoveAbility::ModifyAbilityImpl()
//{
//}

void UMoveAbility::MoveToMarker()
{
	auto* TargetActor = GetTarget<UTargetActor>()->GetTargetActor();

	if(!GetOwnerPathFollowingComponent()->OnRequestFinished.IsBoundToObject(this))
	{
		GetOwnerPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::OnMoveRequestFinished);
	}
	OwnerAsAtom->OnMoveOrderRequested.Broadcast();
	
}

void UMoveAbility::OnMoveRequestFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	
}

AController* UMoveAbility::GetOwnerController() const
{
	//const_cast<UMoveAbility*>(this)->OwnerController = GetOwnerActorAs<APawn>()->GetController();
	return OwnerController;
}

UPathFollowingComponent* UMoveAbility::GetOwnerPathFollowingComponent() const
{
	//const_cast<UMoveAbility*>(this)->OwnerPathFollowingComp = GetOwnerController()->FindComponentByClass<UPathFollowingComponent>();
	return OwnerPathFollowingComp;
}