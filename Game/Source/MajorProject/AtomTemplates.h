#pragma once

#include "CoreMinimal.h"
#include <UObject/UnrealType.h>
#include "Engine/SCS_Node.h"
#include "Engine/BlueprintGeneratedClass.h"
#include <UObject/Field.h>


class AtomTemplates
{
public:

	template<class SearchedClass>
	static SearchedClass* FindComponent(UActorComponent* ContextComponent)
	{
		return ContextComponent ? ContextComponent->GetOwner()->FindComponentByClass<SearchedClass>() : nullptr;
	}
	
	template<class T>
	static T* FindDefaultComponentByClass(const TSubclassOf<AActor> InActorClass)
	{
		static_assert(TPointerIsConvertibleFromTo<T, const UActorComponent>::Value, "'T' template parameter to FindDefaultComponentByClass must be derived from UActorComponent");
		if(IsValid(InActorClass) == false)
		{
			return nullptr;
		}
		//CheckCDO
		AActor* ActorCDO = InActorClass->GetDefaultObject<AActor>();
		if(UActorComponent* FoundComponent = ActorCDO->FindComponentByClass(T::StaticClass()))
		{
			return(T*)(FoundComponent);
		}
		// Check blueprint nodes. Components added in blueprint editor only (and not in code) are not available from CDO.
		UBlueprintGeneratedClass* RootBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InActorClass);
		UClass* ActorClass = InActorClass;
		// Go down the inheritance tree to find nodes that were added to parent blueprints of our blueprint graph.
		do
		{
			const UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass);
			if(ActorBlueprintGeneratedClass == nullptr)
			{
				return nullptr;
			}

			const TArray<USCS_Node*>& ActorBlueprintNodes = ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();
			
			for(const USCS_Node* Node : ActorBlueprintNodes)
			{
				if(Node->ComponentClass->IsChildOf(T::StaticClass()))
				{
					return (T*)Node->GetActualComponentTemplate(RootBlueprintGeneratedClass);
				}
			}
				ActorClass = Cast<UClass>(ActorClass->GetSuperStruct());
			
		}while (ActorClass != AActor::StaticClass());
		return nullptr;
	}
	
};