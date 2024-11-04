#include "MoveMarker.h"

AMoveMarker::AMoveMarker()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	//create object
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	SetActorEnableCollision(false);
	SetHidden(true);
}

void AMoveMarker::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void AMoveMarker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bFollowingActor)
	{
		if(ActorToFollow)
		{
			SetActorLocation(ActorToFollow->GetActorLocation());
		}
		else
		{
			FinishActorFollow();
		}
	}
}

void AMoveMarker::FollowActor(AActor* Actor)
{
	SetActorLocation(Actor->GetActorLocation());
	ActorToFollow = Actor;
	bFollowingActor = true;
}

void AMoveMarker::PlaceMarkerAtLocation(FVector Location)
{
	if(bFollowingActor)
	{
		FinishActorFollow();
	}
	SetActorLocation(Location);
}

void AMoveMarker::FinishActorFollow()
{
	ActorToFollow = nullptr;
	bFollowingActor = false;
}

AActor* AMoveMarker::GetFollowedActor() const
{
	return ActorToFollow;
}

void AMoveMarker::BeginPlay()
{
	Super::BeginPlay();
	
}



