// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for Firing Status.
UENUM()
enum class EFiringStatus : uint8 {
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo,
};

// Forward Delaration.
class UTankBarrel; 
class UTankTurret;
class AProjectile;


// Hold barrel's property and Elevate barrel.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Firing Status")
	EFiringStatus GetFiringStatus() const;

	void AimAt(FVector);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmo() const;


private:
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelToward(FVector);
	double LastFireTime = 0;
	

	UPROPERTY(EditAnyWhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnyWhere, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	bool IsBarrelMoving() const;

	FVector AimDirection;

	bool isReloaded() const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 3;
};