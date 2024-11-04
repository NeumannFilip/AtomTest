#pragma once

#include "AtomCharacter.h"
#include "GameFramework/Character.h"
#include "AtomPlayerCharacter.generated.h"


class AAtomCursor;
class AAtomController;

UCLASS()
class MAJORPROJECT_API AAtomPlayerCharacter : public AAtomCharacter
{
	GENERATED_BODY()

public:
	AAtomPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	void SpawnController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Serialize(FArchive& Ar) override;


	virtual void BeginPlay() override;

protected:

	//virtual void SetupPlayerInputMode() override;
	//virtual void SetupInputComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	//cursor?
	UPROPERTY()
	AAtomController* KeyboardAndMouseController;

	UPROPERTY(Transient)
	AAtomCursor* Cursor;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AAtomController> KeyboardAndMouseControllerClass;
};
