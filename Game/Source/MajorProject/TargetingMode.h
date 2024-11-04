#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "TargetingMode.generated.h"

class AActor;

//Class that is support class for UAbility System
//Its intent is to provide validation for abilities.
//In situations where players aims cursor at objects it needs a lot information like:
//what is the object that cursor is on
//is it correct target etc.
UCLASS()
class UTargetingMode : public UObject
{
		GENERATED_BODY()
	
public:
	virtual void Initialize(UClass* InTargetClass);
	bool IsActorValidForTarget(const AActor* Actor) const;
	virtual FVector GetTargetLocationForActor(const AActor* Actor) const;

	void SetPreviewTarget(AActor* Actor);
	virtual void SetPreviewTarget(const TArray<AActor*>& Actors);
	UTarget* GetPreviewTarget() const;

	virtual UTarget* CollectPreviewTarget();
	
	UPROPERTY()
	UTarget* PreviewTarget;
	
protected:

	UClass* TargetClass;

	virtual bool IsActorValidForTargetImplementation(const AActor* Actor) const {return true; };
	virtual void InitializeTargetingModeImplementation() {};
};
