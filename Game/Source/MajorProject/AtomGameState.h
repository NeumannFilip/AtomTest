#pragma once
#include <CoreMinimal.h>
#include "GameFramework/GameStateBase.h"
#include "GameplayTagContainer.h"
#include "AtomGameState.generated.h"

class UAtom;

//Simple way of tracking atoms aka players in the game 
UCLASS()
class UAtomManager : public UObject
{
	GENERATED_BODY()

public:

	TArray<FName> GetAtomIds() const;

	AActor* GetAtom(FGameplayTag AtomId) const;
	void GetAtoms(TArray<AActor*>& OutAtoms) const;
	UPROPERTY()
	TArray<UAtom*> Atoms;
};

UCLASS()
class AAtomGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AAtomGameState();

	//I will skip stuff like game over etc. even tho they should be here


	void RegisterPlayerAtom(UAtom* AtomToRegister);
	void UnRegisterPlayerAtom(UAtom* AtomToUnregister);

	UPROPERTY()
	UAtomManager* PlayerAtoms;
	UPROPERTY()
	UAtomManager* EnemyAtoms;

	UAtom* GetAtom(FName Id)const;

	UPROPERTY()
	TMap<FName, UAtom*> Atoms;
	UPROPERTY()
	TMap<FName, AActor*> Actors;
	
};
