// Copyright Epic Games, Inc. All Rights Reserved.

#include "MajorProjectGameMode.h"

#include "Atom.h"
#include "AtomPlayerController.h"
#include "MajorProjectPlayerController.h"
#include "MajorProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMajorProjectGameMode::AMajorProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAtomPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Content/Character/BP_AtomPlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Content/Character/BP_AtomController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

UAtom* AMajorProjectGameMode::SpawnAtom(const TSubclassOf<AActor>& ActorClass, FTransform const& Transform, FName Name)
{

	if(const AActor* ActorCDO = ActorClass->GetDefaultObject<AActor>())
	{
		if(const UAtom* DefaultAtom = ActorCDO->FindComponentByClass<UAtom>())
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
	}
	return nullptr;
}

void AMajorProjectGameMode::RegisterAtom(UAtom* UnitToRegister)
{
	Atoms.Add(UnitToRegister->GetOwner()->GetFName(),UnitToRegister);
}

void AMajorProjectGameMode::SpawnAtom(FName Id)
{
	/*if(const auto* PlayerController = GetWorld()->GetFirstPlayerController<AAtomPlayerController>())
	{
		const FTransform = PlayerController->GetCursor()->GetActorTransform();
		SpawnAtomAtLocation(Id, Transform);
	}*/
}

void AMajorProjectGameMode::RemoveAtom(FName Id)
{
}

void AMajorProjectGameMode::SpawnAtomAtLocation(FName Id, FTransform Transform)
{
}

void AMajorProjectGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void AMajorProjectGameMode::OnMatchStartedHandler()
{
}

void AMajorProjectGameMode::Setup()
{
}
