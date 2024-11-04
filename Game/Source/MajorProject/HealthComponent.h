// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//Adding Delegates to allow calling this class
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FHealthComponentValueChangedByInstigatorDelegate, UHealthComponent*, HealthComponent, int32, NewValue, int32, OldValue, int32, Amount, AActor*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthComponentInstigatorDelegate, UHealthComponent*, HealthComponent, AActor*, Instigator);


//I am thinking that I can use health component for few things thus I will now expand it

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAJORPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void Serialize(FArchive& Ar) override;

	//Custom classes
	UFUNCTION(BlueprintCallable)
	int32 Heal(int32 Value, AActor* Instigator);
	UFUNCTION(BlueprintCallable)
	virtual void Damage(int32 Value, AActor* Instigator);
	UFUNCTION(BlueprintCallable)
	void Kill(AActor* Instigator);
	void Resurrect(AActor* Instigator);
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; };
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return CurrentHealth; };
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bDead && IsValid(GetOwner()); } // Checks bDead and IsPendingKill.


	void SetStartingHealth(int32 Value);


	UPROPERTY(BlueprintAssignable)
	FHealthComponentValueChangedByInstigatorDelegate OnHealed;
	UPROPERTY(BlueprintAssignable)
	FHealthComponentValueChangedByInstigatorDelegate OnDamaged;
	UPROPERTY(BlueprintAssignable)
	FHealthComponentInstigatorDelegate OnPreDied;
	UPROPERTY(BlueprintAssignable)
	FHealthComponentInstigatorDelegate OnDied;


private:
	void Died(AActor* Instigator);
	UPROPERTY()
	AActor* DeathInstigator;
	
	UPROPERTY()
	bool bDead;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent|Health")
	int32 StartingHealth = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent|Health")
	int32 MaxHealth = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthComponent|Health")
	int32 CurrentHealth = -1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent|Health")
	bool bInvulnerable;
};
