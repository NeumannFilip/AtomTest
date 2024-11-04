#pragma once
#include "AtomController.h"

#include  "AtomMainController.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputMode : uint8
{
	KeyboardAndMouse,
	Controller
};

UCLASS()
class AAtomMainController : public APlayerController
{
	GENERATED_BODY()
public:


	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION(BlueprintGetter)
	EPlayerInputMode GetPlayerInputMode() const;
	UFUNCTION(BlueprintCallable)
	void SetPlayerInputMode(EPlayerInputMode NewMode);

	void SetMouseMovementCaptureMode(bool bEnabled);

	UFUNCTION(BlueprintCallable)
	void RefreshPlayerInputMode();


protected:
	// Begin AActor override
	virtual void BeginPlay() override;
	// End AActor override

	virtual void SetupPlayerInputMode();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, BlueprintGetter=GetPlayerInputMode, meta = (AllowPrivateAccess = "true"))
	EPlayerInputMode PlayerInputMode = EPlayerInputMode::KeyboardAndMouse;
};
