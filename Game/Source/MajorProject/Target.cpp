#include "Target.h"

void UTarget::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);
}

void UTarget::TargetPostDuplicate(const UTarget* Src)
{
}
