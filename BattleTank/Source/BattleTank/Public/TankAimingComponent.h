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
	Reloading
};

// Forward Delaration.
class UTankBarrel; 
class UTankTurret;

// Hold barrel's property and Elevate barrel.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

public:	
	void AimAt(FVector, float);
	void SetBarrelReference(UTankBarrel*);
	void SetTurretReference(UTankTurret*);


private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;



	void MoveBarrelToward(FVector);
};
