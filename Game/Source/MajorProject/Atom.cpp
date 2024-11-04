// Fill out your copyright notice in the Description page of Project Settings.


#include "Atom.h"

#include "AbilityComponent.h"
#include "AtomController.h"
#include "AtomPlayerCharacter.h"
#include "AtomPlayerController.h"
#include "MoveMarker.h"
#include "TargetingMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAtom::UAtom()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UAtom::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAtom::PostInitProperties()
{
	Super::PostInitProperties();
}

void UAtom::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAtom::InitializeComponent()
{
	Super::InitializeComponent();
	SpawnMoveMarker();
}

void UAtom::BeginDestroy()
{
	if (GetWorld() && GetWorld()->IsGameWorld())
	{
	GetMoveMarker()->ConditionalBeginDestroy();
	GetMoveMarker()->Destroy();
	}
	Super::BeginDestroy();
	Super::BeginDestroy();
}

void UAtom::Init()
{
	
}

FGameplayTag UAtom::GetAtomID() const
{
	return AtomID;
}

void UAtom::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void UAtom::OrderMove(AActor* TargetActor, bool bDirectCast)
{
	if (UAbility* MoveAbility = GetAbilityComponent()->GetAbility(GetMoveAbilityClass()))
	{
		// We can create our own Target with NewObject and pass it, but going through targeting mode is safe if target type changes.
		MoveAbility->GetTargetingMode()->SetPreviewTarget(TargetActor);
		MoveAbility->StartCast(MoveAbility->GetTargetingMode()->CollectPreviewTarget(), bDirectCast);
	}
}

void UAtom::OrderMove(const FVector& Location, bool bDirectCast)
{
	GetMoveMarker()->PlaceMarkerAtLocation(Location);
	OrderMove(GetMoveMarker(), bDirectCast);
}

void UAtom::StopMovement()
{
	MoveMarker->SetActorHiddenInGame(true);
	MoveMarker->FinishActorFollow();
	MoveMarker->SetActorLocation(GetOwner()->GetActorLocation());
	GetOwner<ACharacter>()->GetCharacterMovement()->StopMovementImmediately();
}


void UAtom::Selected()
{
	bSelected = true;
	OnSelectedChanged.Broadcast(true);
}

void UAtom::Deselected()
{
	bSelected = false;
	OnSelectedChanged.Broadcast(false);
}

bool UAtom::IsSelected()
{
	return bSelected;
}

UAbilityComponent* UAtom::GetAbilityComponent() const
{
	/*if (!AbilityComponent)
	{
		const_cast<AAtom>(this)->AbilityComponent = GetOwner()->FindComponentByClass<UAbilityComponent>();
	}*/
	
	
	return ensure(AbilityComponent), AbilityComponent;
}

UAtomMovementComponent* UAtom::GetAtomMovementComponent() const
{
	return MovementComponent;
}

AMoveMarker* UAtom::GetMoveMarker() const
{
	return MoveMarker;
}

TSubclassOf<UMoveAbility> UAtom::GetMoveAbilityClass() const
{
	return MoveAbilityClass;
}

void UAtom::SpawnMoveMarker()
{
	const TSubclassOf<AMoveMarker> Class = MoveMarkerClass.IsNull() ? AMoveMarker::StaticClass() : MoveMarkerClass.LoadSynchronous();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*FString::Printf(TEXT("MoveMarker_%s"), *GetOwner()->GetName()));
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MoveMarker = GetWorld()->SpawnActor<AMoveMarker>(Class, SpawnParams);
	MoveMarker->FollowActor(GetOwner());
}

void UAtom::BindToMove()
{
	/*if(auto* MoveAbility = GetAbilityComponent()->GetAbility(GetMoveAbilityClass()))
	{
		OnMoveHandle = MoveAbility->OnCastStarted.AddUObject(this, &ThisClass::OnMoveCastStarted);
	}*/
}

void UAtom::UnbindFromMove()
{
	/*if (auto* MoveAbility = GetAbilityComponent()->GetAbility(GetMoveAbilityClass()))
	{
		if (MoveAbility->OnCastStarted.Remove(OnMoveHandle))
		{
			OnMoveHandle.Reset();
		}
	}*/
}