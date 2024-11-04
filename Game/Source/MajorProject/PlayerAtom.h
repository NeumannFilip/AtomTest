#pragma once
#include "Atom.h"


#include "PlayerAtom.generated.h"

//Class that tracks playeable atoms
UCLASS()
class UPlayerAtom : public UAtom
{
	GENERATED_BODY()
public:
	UPlayerAtom(	);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UAtom* GetRedirectedAtom();

	int32 GetAtomIndex() const;

	UPROPERTY()
	TArray<UAtom*> AtomRedirectors;

	UPROPERTY(EditDefaultsOnly)
	int32 AtomIndex = -1;
	
};
