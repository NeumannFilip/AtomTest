// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AtomCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UPlayerMappableInputConfig;
class UFloatingPawnMovement;
class UInputAction;

UCLASS()
class MAJORPROJECT_API AAtomCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAtomCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Serialize(FArchive& Ar) override;

	void FocusOnActor(AActor* FocusedActor, bool bInstant = false);
	void FocusOnLocation(FVector FocusedLocation, bool bInstant = false);
	void StopFocus();
	
	//After investigation of Camera classes and various Camera creation tutorials I acquired a bit of knowledge how to make it? (probably not)

	void AddCameraMovementInput(FVector2D InputVector);
	UFUNCTION(BlueprintCallable)
	void DigitalRotateCamera(float Input);
	UFUNCTION(BlueprintCallable)
	void ZoomCamera(float Input);
	//Returns zoom as arm length

	const FVector2D& GetZoomRange() const;
	
	UFUNCTION(BlueprintPure)
	float GetZoom() const;
	//normalizing zoom range
	float GetZoomFraction() const;
	void SetCameraLocationDirectly(FVector NewLocation);

	UPROPERTY()
	float ZoomTarget;
	//Components :D

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* RootCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* TransformTarget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* ArmRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;
	
	//Inputs

	void SetMouseControlMode(bool bEnabled);
	UFUNCTION()
	void MovementInputTriggered(const FInputActionValue& ActionValue);
	UFUNCTION()
	void MouseRotateSwitchStarted();
	UFUNCTION()
	void MouseRotateSwitchCompleted();
	UFUNCTION()
	void ZoomInputTriggered(const FInputActionValue& ActionValue);

	UFUNCTION(BlueprintCallable)
	void ResetRotationToDefault();
	UFUNCTION(BlueprintCallable)
	void ResetZoomToDefault();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input)
	UInputAction* MouseRotateSwitchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input)
	UInputAction* ZoomAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "false"))
	float DefaultZoom{2900};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMax = 1, ClampMin = 0, UIMax = 1, UIMin = 0))
	float DefaultZoomFraction = 0.3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultCameraArmAngle{-50};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultCameraAngle{4.75};

	UPROPERTY(BlueprintReadOnly)
	bool bFocusing{false};
	UPROPERTY(BlueprintReadOnly)
	AActor* ActorToFocus;
	UPROPERTY(BlueprintReadOnly)
	FVector LocationToFocus;
	
	
	//BeginPlay Values

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Fov{70};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D ZoomRange{200, 5000};

	//TODO:Anything else?
	
protected:
	
	
private:
	UPROPERTY()
	FRotator DefaultRotation;

	
};
