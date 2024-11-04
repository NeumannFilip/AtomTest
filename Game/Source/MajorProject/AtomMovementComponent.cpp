// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomMovementComponent.h"

#include "GameplayTagContainer.h"

void UAtomMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAtomMovementComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void UAtomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UAtomMovementComponent::IsMovingOnGround() const
{
	return Super::IsMovingOnGround();
}

void UAtomMovementComponent::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
}

void UAtomMovementComponent::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
}

float UAtomMovementComponent::GetMaxBrakingDeceleration() const
{
	return Super::GetMaxBrakingDeceleration();
}

void UAtomMovementComponent::DisableMovement()
{
	Super::DisableMovement();
}

void UAtomMovementComponent::AddInputVector(FVector WorldVector, bool bForce)
{
	if(bMovementEnabled)
	{
		Super::AddInputVector(WorldVector, bForce);
	}
}

void UAtomMovementComponent::EnableMovement()
{
	
}

void UAtomMovementComponent::SetSprinting(bool bVal)
{
}

void UAtomMovementComponent::SetSpeedModifier(int32 Val)
{
}

void UAtomMovementComponent::Init()
{
}

void UAtomMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UAtomMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);
}

void UAtomMovementComponent::SupportedGameplayTagChanged(const FGameplayTag Tag, int32 Count)
{
}
