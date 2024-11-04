#pragma once

#include "AtomFunctions.h"
#include "GameValues.generated.h"


UCLASS(Blueprintable,BlueprintType)
class MAJORPROJECT_API UGameValues : public UObject
{
	GENERATED_BODY()
public:
	//Data Table information getters
	UFUNCTION(BlueprintPure)
	static UGameValues* Get(const UObject* WorldContextObject = nullptr);

	UFUNCTION(BlueprintCallable)
	const FLevelInfo& GetLevelData(const FString& LevelName = TEXT("")) const;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSoftClassPtr<class AAtomPlayerCharacter>> PlayerCharacters;

private:
	UPROPERTY(EditDefaultsOnly, Category="Level Data")
	FLevelInfo DefaultLevelData;
	UPROPERTY(EditDefaultsOnly, Category="Level Data")
	TSoftObjectPtr<UDataTable> LevelData;
};
