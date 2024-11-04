// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class UAtom;
class UBillboardComponent;


UCLASS(Abstract)
class MAJORPROJECT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UFUNCTION(BlueprintCallable)
	UAtom* GetSpawnedAtom()const;

	virtual TSubclassOf<AActor> GetClassToSpawn() const;
	virtual UAtom* SpawnAtom();
	void DestroySpawned();
	virtual void PostRegisterAllComponents() override;

	virtual void Serialize(FArchive& Ar) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool ShouldAutoSpawn() const;
	virtual FTransform GetSpawnTransform() const;

	//Part of animations and skeletons that I would love to do, but it was side thing.
	void SetCustomSkeletalMesh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	USkeletalMesh* CustomSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	bool bAutoSpawn = true;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* SceneComp;
	UPROPERTY(VisibleDefaultsOnly)
	UBillboardComponent* BillboardComp;

	UPROPERTY(Transient) 
	TObjectPtr<UAtom> SpawnedAtoms;

	UPROPERTY(Transient)
	TWeakObjectPtr<UAtom> SpawnedAtom;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};