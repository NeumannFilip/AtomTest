#pragma once

#include "AtomLibrary.generated.h"

class UAtom;

UCLASS()
class MAJORPROJECT_API UAtomLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//tracking atoms
	UFUNCTION(BlueprintCallable)
	static AActor* GetPlayerAtom(const UObject* WorldContextObject, FGameplayTag AtomId);
	UFUNCTION(BlueprintCallable)
	static void GetPlayerTeam(const UObject* WorldContextObject, TArray<AActor*>& Team);
	UFUNCTION(BlueprintCallable)
	static AActor* SpawnPlayerAtom(const UObject* WorldContextObject, TSubclassOf<AActor> Class,
	                               AActor* DestinationActor);
	UFUNCTION(BlueprintCallable)
	static void SpawnAtomsFromSpawners(const TArray<ASpawner*> Spawners);
	
	
};