#pragma once

#include "AtomCursor.generated.h"

class AAtomCamera;

UENUM()
enum class EGroundMarkerState : uint8
{
	Default,
	InRange,
	NoLineOfFire
};

UCLASS()
class AAtomCursor : public AActor
{

	GENERATED_BODY()
public:
	AAtomCursor();

	virtual void Tick(float DeltaSeconds) override;

	
	void SetGroundMarkerState(EGroundMarkerState NewState, bool bIgnoreLock = false);
	EGroundMarkerState GetGroundMarkerState() const;
	void SetCursorVisibility(bool bVisible);
	void SetGroundMarkerStateChangeLocked(bool bLock);
	bool IsGroundMarkerStateChangeLocker() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Behaviour")
	FVector2D ScaleRange = FVector2D(0.6f, 1.f);

	// I kinda don't have time to do Material but... maybe I will think of something really quick
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GroundMarkerDefaultMaterial;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GroundMarkerInRangeMaterial;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GroundMarkerNoLineOfFireMaterial;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* GroundMarkerComp;
	
private:

	void TickCameraRelativeScale();

	UPROPERTY(Transient)
	EGroundMarkerState GroundMarkerState = EGroundMarkerState::Default;
	UPROPERTY(Transient)
	AAtomCamera* Camera;
	UPROPERTY(Transient)
	float CameraTargetArmLength = 0.f;
	UPROPERTY(Transient)
	bool bGroundMarkerStateChangeLocked = false;
	
	
};
