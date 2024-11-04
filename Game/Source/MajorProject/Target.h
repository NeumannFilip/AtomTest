#pragma once

#include "Target.generated.h"

UCLASS(Abstract,BlueprintType)
class UTarget : public UObject
{

	/*
	 *UTarget manages a single target actor in a game, allowing you to set, get, and clear the
	 *target. It extends UTarget, an abstract class for general target management. */
	GENERATED_BODY()
public:

	// Begin UObject override
	virtual void Serialize(FArchive& Ar) override;
	// End UObject override

	virtual void TargetPostDuplicate(const UTarget* Src);;
	
	virtual void SetTarget(const TArray<AActor*>& Actors) {};
	/** May always be nullptr on some target types! */
	virtual AActor* TryGetTargetActor() const { return nullptr; };
	virtual bool IsTargetSet() const { return true; };
	UFUNCTION(BlueprintCallable)
	virtual void ClearAll() {};
	
	UFUNCTION(BlueprintCallable)
	virtual void SetTarget(AActor* Actor) { SetTarget(TArray{Actor}); };
};
