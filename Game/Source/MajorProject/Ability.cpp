// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"

void UAbility::PostInitProperties()
{
	UObject::PostInitProperties();
}

bool UAbility::StartCast(UTarget* InTarget, bool bWithModifier)
{

	

	return false;
}


void UAbility::Activate()
{
}

void UAbility::Deactivate()
{
}

void UAbility::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);
}

UTarget* UAbility::GetTarget() const
{
	return Target;
}

void UAbility::Cast_Internal()
{
}

void UAbility::FinishAbility()
{
}

AActor* UAbility::GetOwnerActor() const
{
	return OwnerActor;
}

FName UAbility::GetAbilityName() const
{
	return Name;
}

UTargetingMode* UAbility::GetTargetingMode() const
{
	return TargetingMode;
}
