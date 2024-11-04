#include "AtomInstance.h"
#include "GameValues.h"

UAtomInstance::UAtomInstance()
{
}

UGameValues* UAtomInstance::GetGameValues() const
{
	const auto* Class = GameValuesClass.LoadSynchronous();
	check(Class);
	return Class->GetDefaultObject<UGameValues>();
}
