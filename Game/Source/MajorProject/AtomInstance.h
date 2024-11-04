#pragma once

#include "AtomInstance.generated.h"
class UGameValues;

UCLASS()
class UAtomInstance : public UGameInstance
{
	GENERATED_BODY()
	UAtomInstance();
public:

	//load data
	UGameValues*  GetGameValues() const;

private:
	UPROPERTY(EditDefaultsOnly, NoClear)
	TSoftClassPtr<UGameValues> GameValuesClass;
};
