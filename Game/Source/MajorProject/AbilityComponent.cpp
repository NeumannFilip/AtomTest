// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

#include "Ability.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UAbility* UAbilityComponent::GetAbility(const TSubclassOf<UAbility> AbilityClass, bool bIncludeChildren) const
{
	return GetAbilityRaw(AbilityClass, bIncludeChildren);
}


UAbility* UAbilityComponent::GetAbility(const FName Name)
{
	for(const auto& Ability : Abilities)
	{
		if(Ability.Value->GetAbilityName() == Name)
		{
			return Ability.Value;
		}
	}
	return nullptr;
}

UAbility* UAbilityComponent::GetAbilityRaw(const UClass* AbilityClass, bool bIncludeChildren) const
{
	if(bIncludeChildren)
	{
		for (const auto& AbilityTuple : Abilities)
		{
			if(AbilityTuple.Key->IsChildOf(AbilityClass))
			{
				return AbilityTuple.Value;
			}
		}
	}
	return Abilities.FindRef(AbilityClass);
}

UAbility* UAbilityComponent::AddAbility(const TSubclassOf<UAbility>& AbilityClass)
{
	if(Abilities.Contains(AbilityClass))
	{
		return nullptr;
	}
	UAbility* NewAbility = NewObject<UAbility>(this,AbilityClass);
	AddAbility(NewAbility);
	return NewAbility;
}

void UAbilityComponent::AddAbility(UAbility* Ability)
{
	Abilities.Add(Ability->GetClass(),Ability);
}

// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilityComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

