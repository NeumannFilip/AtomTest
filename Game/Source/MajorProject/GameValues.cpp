#include "GameValues.h"

#include "GameMapsSettings.h"
#include "AtomInstance.h"


UGameValues* UGameValues::Get(const UObject* WorldContextObject)
{
	if(WorldContextObject)
	{
		if( auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			if( auto* GameInstance = World->GetGameInstance<UAtomInstance>())
			{
				return GameInstance->GetGameValues();
			}
		}
	}
	const FSoftClassPath GameInstanceClassName = GetDefault<UGameMapsSettings>()->GameInstanceClass;
	if(UClass* GameInstanceClass = GameInstanceClassName.TryLoadClass<UAtomInstance>())
	{
		return GetDefault<UAtomInstance>(GameInstanceClass)->GetGameValues();
	}
	return nullptr;
}

const FLevelInfo& UGameValues::GetLevelData(const FString& LevelName) const
{
	if(LevelName.IsEmpty() == false)
	{
		if(const auto* Data = LevelData.LoadSynchronous())
		{
			static const FString Context = FString(TEXT("UGameValues::GetLevelData"));
			if(auto* Row = Data->FindRow<FLevelInfo>(FName(*LevelName),Context,false))
			{
				return *Row;
			}
		}
	}
	return DefaultLevelData;
}
