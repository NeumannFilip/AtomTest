// Fill out your copyright notice in the Description page of Project Settings.


#include "AAtomGameMode.h"

#include "AbilityComponent.h"
#include "Atom.h"
#include "AtomCursor.h"
#include "AtomGameState.h"
#include "AtomPlayerController.h"
#include "EngineUtils.h"
#include "GameValues.h"
#include "PlayerSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "AtomTemplates.h"
#include "AtomPlayerCharacter.h"

class AAtomGameState;

AAAtomGameMode::AAAtomGameMode()
{
}

void AAAtomGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AAAtomGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	Setup();
}

UAtom* AAAtomGameMode::SpawnAtom(const TSubclassOf<AActor>& ActorClass, FTransform const& Transform, FName Name)
{
	//Usage of the template to search for class owenr
	if(const auto* DefaultAtom = AtomTemplates::FindDefaultComponentByClass<UAtom>(ActorClass);ensure(DefaultAtom))
	{
			FActorSpawnParameters SpawnParameters;

			SpawnParameters.Name  = ActorClass->GetFName();
			if(DefaultAtom->bUnique)
			{
				check(Name.IsNone() || SpawnParameters.Name.IsEqual(Name));
			}
			else
			{
				int32& Index = NameIndex.FindOrAdd(SpawnParameters.Name);
				if(Name.IsNone())
				{
					//all of this in situation with more characters at the same time 
					SpawnParameters.Name = FName(SpawnParameters.Name, ++Index);
					SpawnParameters.Name = Name;
				}
			}
			SpawnParameters.NameMode=FActorSpawnParameters::ESpawnActorNameMode::Required_ErrorAndReturnNull;

			const FRotator Rotation = FRotator(0, Transform.Rotator().Yaw, 0);
			if(const AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorClass,Transform.GetLocation(),Rotation,SpawnParameters))
			{
				return NewActor->FindComponentByClass<UAtom>();
			}
	}
	return nullptr;
}

void AAAtomGameMode::RegisterAtom(UAtom* AtomToRegister)
{
	Atoms.Add(AtomToRegister->GetOwner()->GetFName(),AtomToRegister);
}

void AAAtomGameMode::SpawnAtom(FName Id)
{
	if(const auto* PlayerController = GetWorld()->GetFirstPlayerController<AAtomPlayerController>())
	{
		const FTransform Transform = PlayerController->GetCursor()->GetActorTransform();
		SpawnAtomAtLocation(Id, Transform);
	}
}

void AAAtomGameMode::RemoveAtom(FName Id)
{
}

void AAAtomGameMode::SpawnAtomAtLocation(FName Id, FTransform Transform)
{
	const auto* Values = UGameValues::Get();
	auto& LevelData = Values->GetLevelData();
	const auto& CharacterSoftPtr = Values->PlayerCharacters.FindRef(Id);
	for(const auto& AtomRecord : LevelData.Squad)
	{
		if(AtomRecord.Class == CharacterSoftPtr)
		{
			SpawnSquadAtom(AtomRecord,Transform);
			return;
		}
	}
}

void AAAtomGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void AAAtomGameMode::OnMatchStartedHandler()
{
}

void AAAtomGameMode::Setup()
{
	SpawnSquad();
}

void AAAtomGameMode::SpawnSquad()
{
	//get information and spawn team
	const auto* Values = UGameValues::Get();
	const FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
	const FLevelInfo& LevelInfo = Values->GetLevelData(LevelName);

	TMap<TSubclassOf<AActor>, APlayerSpawner*> Spawners;
	for(TActorIterator<APlayerSpawner> It(GetWorld()); It; ++It)
	{
		APlayerSpawner* Spawner = *It;
		if(auto Class = Spawner->GetClassToSpawn(); ensure(Class))
		{
			Spawners.Add(Class,Spawner);
		}
	}

	for(const auto& Atom : LevelInfo.Squad)
	{
		if(TSubclassOf<AActor> Class = Atom.Class.LoadSynchronous())
		{
			if(APlayerSpawner* Spawner; Spawners.RemoveAndCopyValue(Class, Spawner))
			{
				SpawnSquadAtom(Atom,Spawner->GetActorTransform());
			}
		}
	}
	
}

void AAAtomGameMode::SpawnSquadAtom(const FSquadRecord& SquadAtom, FTransform const& Transform)
{
	if(const TSubclassOf<AActor> Class = SquadAtom.Class.LoadSynchronous())
	{
		if(const auto* Atom = GetGameState<AAtomGameState>()->GetAtom(Class->GetFName()))
		{
			return;
		}
		if(auto* Atom = SpawnAtom(Class,Transform))
		{
			if(auto* AbilityComp = Atom->GetOwner()->FindComponentByClass<UAbilityComponent>())
			{
				for(const auto& AbilitySoftClass : SquadAtom.Abilities) 
				{
					if(auto* AbilityClass = AbilitySoftClass.LoadSynchronous())
					{
						AbilityComp->AddAbility(AbilityClass);
					}
				}
			}
			GetGameState<AAtomGameState>()->RegisterPlayerAtom(Atom);
		}
	}
}
