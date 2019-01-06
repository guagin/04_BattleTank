// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Delaration.
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere)
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* Turret);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	void AimAt(FVector HitLocation);
private:
	UPROPERTY(EditAnyWhere, Category = Firing)
	float LaunchSpeed = 1000;
};