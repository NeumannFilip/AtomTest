// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AtomMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EAtomMovementMode : uint8
{
	None,
	Walk,
	Sprint,
};

//I am basically overriding a lot of functions form the parent class
UCLASS()
class MAJORPROJECT_API UAtomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void Serialize(FArchive& Ar) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool IsMovingOnGround() const override;
	// do need a crouch? maybe
	virtual void Crouch(bool bClientSimulation) override;
	virtual void UnCrouch(bool bClientSimulation) override;

	virtual float GetMaxBrakingDeceleration() const override;
	
	virtual void DisableMovement() override;

	virtual void AddInputVector(FVector WorldVector, bool bForce) override;

	UFUNCTION(BlueprintCallable)
	void EnableMovement();


	void SetSprinting(bool bVal);
	bool GetSprinting() const {return bSprinting ;}
	//Navlinks...........
	//Navlinks are difficult and tricky to handle and would only be usable for buildings, any kind of doors, stairs, elevators, ladders
	//Thus for now I am not touching them

	UPROPERTY(Category="Atom Movement: Custom Movement", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float MaxSprintSpeed = 1000;

	void SetSpeedModifier(int32 Val);
protected:

	virtual void Init();

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	UFUNCTION()
	void SupportedGameplayTagChanged(const FGameplayTag Tag, int32 Count);
	//Depending on number of form of movement I could create a struct to handle the cases
	// Ofc walking, sprinting but also potentially crouch / climb / maybe a cast with abilities


	UPROPERTY()
	bool bMovementEnabled = true;
	UPROPERTY(BlueprintReadOnly)
	bool bCasting;
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool bSprinting;

	
};
