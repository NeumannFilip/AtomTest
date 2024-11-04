// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MajorProjectGameMode.generated.h"


class UAtom;

UCLASS(minimalapi)
class AMajorProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMajorProjectGameMode();

	UAtom* SpawnAtom(const TSubclassOf<AActor>& ActorClass, FTransform const& Transform, FName Name = NAME_None);

	void RegisterAtom(UAtom* UnitToRegister);
	
	UFUNCTION(exec)
	void SpawnAtom(FName Id);

	UFUNCTION(exec, BlueprintCallable)
	void RemoveAtom(FName Id);

	UFUNCTION(BlueprintCallable)
	void SpawnAtomAtLocation(FName Id, FTransform Transform);
	virtual void PostSeamlessTravel() override;

	void OnMatchStartedHandler();

	void Setup();

protected:
	UPROPERTY()
	TMap<FName, int32> NameIndex;
	UPROPERTY()
	TMap<FName, UAtom*> Atoms;
};



