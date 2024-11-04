#pragma once

#include "Spawner.h"
#include "PlayerSpawner.generated.h"

class AAtomPlayerCharacter;
class PlayerSpawner;

UCLASS()
class APlayerSpawner : public ASpawner
{
	GENERATED_BODY()

	APlayerSpawner();

public:

	virtual UAtom* SpawnAtom() override;
	virtual TSubclassOf<AActor> GetClassToSpawn() const override;

	virtual void PostLoad() override;

protected:

	virtual FTransform GetSpawnTransform() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<AAtomPlayerCharacter> PlayerClass;

	UPROPERTY()
	TArray<TSoftClassPtr<AAtomPlayerCharacter>> AtomsToSpawn;

	
	
};
