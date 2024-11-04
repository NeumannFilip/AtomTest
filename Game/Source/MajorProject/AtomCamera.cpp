// Fill out your copyright notice in the Description page of Project Settings.


#include "AtomCamera.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AAtomCamera::AAtomCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCollision = CreateDefaultSubobject<USphereComponent>("RootCollision");
	SetRootComponent(RootCollision);

	TransformTarget = CreateDefaultSubobject<USceneComponent>("TransformTarget");
	TransformTarget->SetupAttachment(RootCollision);

	ArmRoot = CreateDefaultSubobject<USceneComponent>("ArmRoot");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(ArmRoot);
	SpringArm->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, DefaultCameraArmAngle, 0)));
	SpringArm->TargetArmLength = DefaultZoom;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, DefaultCameraAngle, 0)));
	Camera->FieldOfView = Fov;
}

// Called when the game starts or when spawned
void AAtomCamera::BeginPlay()
{
	Super::BeginPlay();

	DefaultZoom = FMath::Lerp(ZoomRange.X, ZoomRange.Y, DefaultZoomFraction );
	ZoomTarget = DefaultZoom;
}

// Called every frame
void AAtomCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Delta = GetWorld()->DeltaRealTimeSeconds;
	
}

// Called to bind functionality to input
void AAtomCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MovementInputTriggered);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::ZoomInputTriggered);
		EnhancedInputComponent->BindAction(MouseRotateSwitchAction, ETriggerEvent::Started, this, &ThisClass::MouseRotateSwitchStarted);
		EnhancedInputComponent->BindAction(MouseRotateSwitchAction, ETriggerEvent::Completed, this, &ThisClass::MouseRotateSwitchCompleted);
	}
}

void AAtomCamera::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

void AAtomCamera::FocusOnActor(AActor* FocusedActor, bool bInstant)
{
	if (bInstant)
	{
		SetCameraLocationDirectly(FocusedActor->GetActorLocation());
	}
}

void AAtomCamera::FocusOnLocation(FVector FocusedLocation, bool bInstant)
{
	StopFocus();
	if (bInstant)
	{
		SetCameraLocationDirectly(FocusedLocation);
		return;
	}
	LocationToFocus = FocusedLocation;
	bFocusing = true;
}

void AAtomCamera::StopFocus()
{
}

void AAtomCamera::AddCameraMovementInput(FVector2D InputVector)
{
	
}

void AAtomCamera::DigitalRotateCamera(float Input)
{
}

void AAtomCamera::ZoomCamera(float Input)
{
}

const FVector2D& AAtomCamera::GetZoomRange() const
{
	return ZoomRange;
}

float AAtomCamera::GetZoom() const
{
	return SpringArm->TargetArmLength;
}

float AAtomCamera::GetZoomFraction() const
{
	return FMath::GetMappedRangeValueClamped(ZoomRange,FVector2D(0,1),GetZoom());
}

void AAtomCamera::SetCameraLocationDirectly(FVector NewLocation)
{
	SetActorLocation(NewLocation);
	ArmRoot->SetWorldLocation(NewLocation);
}

void AAtomCamera::SetMouseControlMode(bool bEnabled)
{
}

void AAtomCamera::MovementInputTriggered(const FInputActionValue& ActionValue)
{
}

void AAtomCamera::MouseRotateSwitchStarted()
{
}

void AAtomCamera::MouseRotateSwitchCompleted()
{
}

void AAtomCamera::ZoomInputTriggered(const FInputActionValue& ActionValue)
{
}

void AAtomCamera::ResetRotationToDefault()
{
	SetActorRotation(DefaultRotation);
}

void AAtomCamera::ResetZoomToDefault()
{
	ZoomTarget = DefaultZoom;
}

