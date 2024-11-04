// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

int32 UHealthComponent::Heal(int32 Value, AActor* Instigator)
{
	// I do not want to heal right now, leaving it 
	return Value;
}

void UHealthComponent::Damage(int32 Value, AActor* Instigator)
{
	if(IsDead())
	{
		return;
	}
	const float OldHealth = CurrentHealth;
	OnDamaged.Broadcast(this, CurrentHealth,OldHealth,Value,Instigator);
	if(CurrentHealth <= 0)
	{
		Died(Instigator);
	}
}

void UHealthComponent::Kill(AActor* Instigator)
{
	Damage(GetMaxHealth(),Instigator);
}

void UHealthComponent::Resurrect(AActor* Instigator)
{
}

void UHealthComponent::SetStartingHealth(int32 Value)
{
	StartingHealth = Value;
}

void UHealthComponent::Died(AActor* Instigator)
{
	OnPreDied.Broadcast(this, Instigator);
	bDead = true;
	DeathInstigator = Instigator;
	OnDied.Broadcast(this, Instigator);
}

