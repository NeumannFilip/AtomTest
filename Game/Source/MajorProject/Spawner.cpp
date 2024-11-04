// Fill out your copyright notice in the Description page of Project Settings.
#include "Spawner.h"
#include "MajorProjectGameMode.h"
#include "Components/BillboardComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComp);
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	BillboardComp->SetupAttachment(RootComponent);
}

UAtom* ASpawner::GetSpawnedAtom() const
{
	return SpawnedAtoms.Get();
}

TSubclassOf<AActor> ASpawner::GetClassToSpawn() const
{
	return nullptr;
}

UAtom* ASpawner::SpawnAtom()
{
	ensure(SpawnedAtoms == nullptr);
	if(const TSubclassOf<AActor> ActorClass = GetClassToSpawn())
	{
		SpawnedAtoms = GetWorld()->GetAuthGameMode<AMajorProjectGameMode>()->SpawnAtom(ActorClass, GetSpawnTransform());
		if(ensureMsgf(SpawnedAtoms.Get(), TEXT("%s couldnt spawn atom"), *GetName(), *ActorClass->GetName()))
		{
			SetCustomSkeletalMesh();
			return SpawnedAtoms.Get();
		}
	}
	return nullptr;
}

void ASpawner::DestroySpawned()
{
	if(auto* Atom = SpawnedAtoms.Get())
	{
		//SpawnedAtoms.Reset();
	}
}

void ASpawner::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
	//flags?
	
}

void ASpawner::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnAtom();
}

bool ASpawner::ShouldAutoSpawn() const
{
	return bAutoSpawn;
}

FTransform ASpawner::GetSpawnTransform() const
{
	return FTransform(GetActorRotation(), GetActorLocation());
}

void ASpawner::SetCustomSkeletalMesh()
{
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//aligning?