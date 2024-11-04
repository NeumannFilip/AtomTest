#pragma once
#include "TargetingMode.h"

#include "GroundOnlyTargetingMode.generated.h"
UCLASS()

//This class serves purpose of Tagretting mode
class UGroundOnlyTargetingMode : public UTargetingMode
{
	GENERATED_BODY()
	
public:
	UGroundOnlyTargetingMode();

protected:

	virtual bool IsActorValidForTargetImplementation(const AActor* Actor) const override;
};
