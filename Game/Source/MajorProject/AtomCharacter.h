// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AtomCharacter.generated.h"


class UAtom;

UCLASS(Abstract)
class MAJORPROJECT_API AAtomCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAtomCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;
	
	virtual void Serialize(FArchive& Ar) override;
	
	UFUNCTION(BlueprintCallable)
	UAtom* GetAtom() const;
	
protected:
	UPROPERTY()
	UAtom* AtomComponent;
};
