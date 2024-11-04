// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AAtomGameMode.generated.h"

//Forward declarations
struct FSquadRecord;
class UAtom;

/**
 *  Had to create a custom gamemode as the original one blocks in terms of choosing my custom controllers and so on.
 *  Game mode allow to use of custom controllers, atoms, other gameplay elements
 */
UCLASS()
class MAJORPROJECT_API AAAtomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAAtomGameMode();

	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;

	//Spawns an Atom of specified class at a given transform location with a correct name
	UAtom* SpawnAtom(const TSubclassOf<AActor>& ActorClass,FTransform const& Transform, FName Name = NAME_None);

	//Register a spawn atom
	void RegisterAtom(UAtom* AtomToRegister);

	//Console executable function to spawn by its ID
	UFUNCTION(exec)
	void SpawnAtom(FName Id);

	// Remove atom by ID
	UFUNCTION(exec, BlueprintCallable)
	void RemoveAtom(FName Id);

	//Spawning Atom at given location
	UFUNCTION(BlueprintCallable)
	void SpawnAtomAtLocation(FName Id, FTransform Transform);
	virtual void PostSeamlessTravel() override;

	void OnMatchStartedHandler();

	void Setup();


private:
	//spawn a group of atoms
	void SpawnSquad();
	// Spawns individual atom based on the squad it belongs to
	void SpawnSquadAtom(const FSquadRecord& SquadAtom, FTransform const& Transform);
	
protected:
	UPROPERTY()
	TMap<FName, int32> NameIndex;
	UPROPERTY()
	TMap<FName, UAtom*> Atoms;
};
