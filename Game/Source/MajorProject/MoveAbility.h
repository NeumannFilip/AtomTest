#pragma once

#include "Ability.h"
#include "Navigation/PathFollowingComponent.h"

#include "MoveAbility.generated.h"

class UAtom;
class ACharacter;
class AController;
struct FAIRequestID;

UCLASS()
class UMoveAbility : public UAbility
{
	GENERATED_BODY()

public:
	UMoveAbility();

	virtual void Serialize(FArchive& Ar) override;
	virtual bool StartCast(UTarget* InTarget, bool bWithModifier) override;
	bool IsDirectCast() const;

protected:
	//virtual void ModifyAbilityImpl(); //override of ability?
	

private:

	void MoveToMarker();
	void OnMoveRequestFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);
	

	AController* GetOwnerController() const;
	UPathFollowingComponent* GetOwnerPathFollowingComponent() const;

	FVector MoveToLocation = FVector::ZeroVector;

	UPROPERTY()
	UAtom* OwnerAsAtom;

	UPROPERTY()
	bool bPlayerOwner;

	UPROPERTY()
	bool bDirectCast = false;

	UPROPERTY()
	AController* OwnerController;

	UPROPERTY()
	UPathFollowingComponent* OwnerPathFollowingComp;
};
