#pragma once
#include "Target.h"
#include "TargetActor.generated.h"


UCLASS()
class UTargetActor : public UTarget
{

	GENERATED_BODY()
public:

	
	// Begin UObject override
	virtual void Serialize(FArchive& Ar) override;
	// End UObject override
	
	virtual void SetTarget(const TArray<AActor*>& Actors) override;
	virtual void SetTarget(AActor* Actor) override { SetTarget(TArray{Actor}); };
	virtual AActor* TryGetTargetActor() const override;
	virtual bool IsTargetSet() const override;
	virtual void ClearAll() override;

	//Checking the actors
	void SetTargetActor(AActor* Actor);
	AActor* GetTargetActor() const;

	//template for getting the TargetActor
	template <class T>
	T* GetTargetActor() const
	{
		return TargetActor ? Cast<T>(TargetActor) : nullptr;
	}

protected:
	UPROPERTY()
	AActor* TargetActor;
};