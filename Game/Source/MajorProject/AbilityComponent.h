// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"
//Ability component is pretty tricky, because it would nice to have my own instead of using existing GAS system.

class UAbility;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAJORPROJECT_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();

	//Getters
	UAbility* GetAbility(const TSubclassOf<UAbility> AbilityClass, bool bIncludeChildren = false) const;
	UAbility* GetAbility(const FName Name);
	UAbility* GetAbilityRaw(const UClass* AbilityClass, bool bIncludeChildren = false) const;

	//Adds
	UAbility* AddAbility(const TSubclassOf<UAbility>& AbilityClass);
	void AddAbility(UAbility* Ability);
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Serialize(FArchive& Ar) override;



	UPROPERTY()
	TMap<UClass*, UAbility*> Abilities;
		
};
