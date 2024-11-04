#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

class UTargetingMode;
class UTarget;
class AActor;
class UAbilityComponent;
class AAtom;

//Struct for defining Range types.
//Yes, I forgot about infinite -
UENUM(BlueprintType)
enum class EAbilityCastRangeType : uint8
{
	Ranged2D,
	Ranged3D,
	Infinite
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class MAJORPROJECT_API UAbility : public UObject
{
	GENERATED_BODY()

public:

	virtual void PostInitProperties() override;
	virtual bool StartCast(UTarget* InTarget, bool bWithModifier = false);
	virtual void Activate();
	virtual void Deactivate();
	virtual void Serialize(FArchive& Ar) override;


	//Getters
	UFUNCTION(BlueprintCallable)
	FName GetAbilityName() const;
	UFUNCTION(BlueprintCallable)
	UTargetingMode* GetTargetingMode() const;

	UPROPERTY()
	UTargetingMode* TargetingMode;


	/// Templates
	/** This uses Checked Cast so if cast fails game will crash. So be sure object is of type passed in template argument! */
	template <class T>
	T* GetTargetingMode() const
	{
		return CastChecked<T>(GetTargetingMode());
	}

	/** This uses Checked Cast so if cast fails game will crash. So be sure object is of type passed in template argument! */
	template <class T>
	T* GetTarget() const
	{
		return CastChecked<T>(GetTarget());
	}

	UTarget* GetTarget() const;
	
protected:

	//UPROPERTY()
	//UTarget* Target;
	UPROPERTY()
	AActor* OwnerActor;

private:
	void Cast_Internal();
	void FinishAbility();

	UPROPERTY()
	UTarget* Target;
	
	UPROPERTY()
	UAbilityComponent* AbilityComponent;

protected:

	UPROPERTY()
	UClass* TargetClass;
	UPROPERTY()
	UClass* TargetingModeClass;

	AActor* GetOwnerActor()const;
	
	template <class T>
	T* GetOwnerActorAs() const
	{
		return CastChecked<T>(GetOwnerActor());
	}


	
// enums for states?
	//like interruption?
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;
	//In this case for movement 2D works
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAbilityCastRangeType CastRangeType = EAbilityCastRangeType::Ranged2D;

	//Can ability be casted?
	//I can do rough idea of settings defining if ability can be casted but I don't think it's necessary right now.
	//TODO ^^ ?
	UPROPERTY()
	bool bSignificant = true;
	UPROPERTY()
	bool bAllowCastFromActivatedState = false;
};