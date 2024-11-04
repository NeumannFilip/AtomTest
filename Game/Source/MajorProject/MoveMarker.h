#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveMarker.generated.h"

//I need a way to make player go whereever I want him to go.
// One way of doing that is move marker so ordering a player where to move ( ideally with option to hold a RMB and the order would update like in Diablo games)
// Other way would be to do by tile like in xcom or civ games. 
UCLASS()
class MAJORPROJECT_API AMoveMarker : public AActor
{
	GENERATED_BODY()
	
public:	

	AMoveMarker();
	virtual void Serialize(FArchive& Ar) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	virtual void FollowActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void PlaceMarkerAtLocation(FVector Location);

	//
	UFUNCTION(BlueprintCallable)
	void FinishActorFollow();

	UFUNCTION(BlueprintCallable)
	AActor* GetFollowedActor() const;
	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* SceneComponent;

private:
	UPROPERTY()
	bool bFollowingActor;
	UPROPERTY()
	AActor* ActorToFollow;

};
