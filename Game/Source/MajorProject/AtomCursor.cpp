#include "AtomCursor.h"

#include "AtomCamera.h"
#include "GameFramework/SpringArmComponent.h"

AAtomCursor::AAtomCursor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	GroundMarkerComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground Marker"));
	GroundMarkerComp->SetupAttachment(SceneRoot);
	GroundMarkerComp->SetCollisionProfileName("NoCollision");
}

void AAtomCursor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TickCameraRelativeScale();
}

void AAtomCursor::SetGroundMarkerState(EGroundMarkerState NewState, bool bIgnoreLock)
{
	if (NewState == GroundMarkerState || (!bIgnoreLock && bGroundMarkerStateChangeLocked))
	{
		return;
	}
	
	switch (NewState)
	{
	case EGroundMarkerState::Default:
		GroundMarkerComp->SetMaterial(0, GroundMarkerDefaultMaterial);
		break;
	case EGroundMarkerState::InRange:
		GroundMarkerComp->SetMaterial(0, GroundMarkerInRangeMaterial);
		break;
	case EGroundMarkerState::NoLineOfFire:
		GroundMarkerComp->SetMaterial(0, GroundMarkerNoLineOfFireMaterial);
		break;
	}
	GroundMarkerState = NewState;
}


EGroundMarkerState AAtomCursor::GetGroundMarkerState() const
{
	return GroundMarkerState;
}

void AAtomCursor::SetCursorVisibility(bool bVisible)
{
	SetActorHiddenInGame(!bVisible);
}

void AAtomCursor::SetGroundMarkerStateChangeLocked(bool bLock)
{
	if (bLock != bGroundMarkerStateChangeLocked)
	{
		bGroundMarkerStateChangeLocked = bLock;
	}
}

bool AAtomCursor::IsGroundMarkerStateChangeLocker() const
{
	return bGroundMarkerStateChangeLocked;
}

void AAtomCursor::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetWorld()->GetFirstPlayerController()->GetPawn<AAtomCamera>();
}

void AAtomCursor::TickCameraRelativeScale()
{
	if (Camera && CameraTargetArmLength != Camera->SpringArm->TargetArmLength)
	{
		CameraTargetArmLength = Camera->SpringArm->TargetArmLength;
		const FVector2D& ZoomRange = Camera->GetZoomRange();
		SetActorScale3D(FVector(FMath::GetMappedRangeValueClamped(ZoomRange, ScaleRange, CameraTargetArmLength)));
	}
}
