// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomCharacter.h"

#include "Components/CapsuleComponent.h"
#include "AtomMovementComponent.h"

#include "Atom.h"


AAtomCharacter::AAtomCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAtomMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	//componets will go here

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationYaw = false;
}

void AAtomCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	AtomComponent = FindComponentByClass<UAtom>();
	
	ensure(AtomComponent);
	
}

void AAtomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAtomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAtomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAtomCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AAtomCharacter::BeginDestroy()
{
	Super::BeginDestroy();
}

void AAtomCharacter::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

UAtom* AAtomCharacter::GetAtom() const
{
	return AtomComponent;
}

