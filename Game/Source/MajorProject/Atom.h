// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MoveAbility.h"
#include "Components/ActorComponent.h"
#include "Atom.generated.h"


class AMoveMarker;
class UAtomMovementComponent;
class UAbilityComponent;

DECLARE_MULTICAST_DELEGATE(FAtomDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FAtomBoolDelegate, bool);

UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAJORPROJECT_API UAtom : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAtom();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostInitProperties() override;
	virtual void InitializeComponent() override;
	virtual void BeginDestroy() override;

	virtual void Init();

	UFUNCTION(BlueprintPure)
	FGameplayTag GetAtomID() const;

	//Serialize would serve as a save system
	//I think saving would be cool, idk if really required in this project, but I found it out recently and seems really interesting
	//it could be good for handling reloading movement etc.
	virtual void Serialize(FArchive& Ar) override;

	//for games like xcom / baldurs gate you need to select and deselect characters. 


	//they also need to move so in some way I need to create a ordermovement

	virtual void OrderMove(AActor* TargetActor, bool bDirectCast = false);
	virtual void OrderMove(const FVector& Location, bool bDirectCast = false);
	virtual void StopMovement();
	

	void Selected();
	void Deselected();
	bool IsSelected();

	FAtomBoolDelegate OnSelectedChanged;

	//This will serve me as a movement Ability


	FAtomDelegate OnMoveOrderRequested;
	
	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const;
	UAtomMovementComponent* GetAtomMovementComponent()const;
	AMoveMarker* GetMoveMarker()const;
	TSubclassOf<UMoveAbility> GetMoveAbilityClass() const;

	UPROPERTY(EditDefaultsOnly)
	bool bUnique;
	
protected:
	
	UPROPERTY(Getter, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	FGameplayTag AtomID;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UMoveAbility> MoveAbilityClass = UMoveAbility::StaticClass();

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSoftClassPtr<AMoveMarker> MoveMarkerClass;
	
private:
	// I will definetely need movement
	// so probably I will need classes like
	// void BindToMovement
	// void UnBindFromMovement
	// Delegate OnMovementHandle

	
	//technically with ability system that I want to add maybe i could connect movement with ability ???
	// it makes sense as in combat movement is type of a "ability" that defines how can u move or how long

	void SpawnMoveMarker();
	void BindToMove();
	void UnbindFromMove();
	FDelegateHandle OnMoveHandle;

	UPROPERTY()
	bool bSelected = false;


	UPROPERTY()
	UAbilityComponent* AbilityComponent;
	UPROPERTY()
	AMoveMarker* MoveMarker;
	UPROPERTY()
	UAtomMovementComponent* MovementComponent;

	
};