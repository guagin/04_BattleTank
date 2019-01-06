// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/GameplayStaticsTypes.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LanchSpeed) {
	if (!Barrel) {
		return;
	}
	FString TankName = GetOwner()->GetName();
	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector EndLocation = HitLocation;
	
	FCollisionResponseParams ResponseParam; // dafaq it this shit???
	TArray <AActor*> ActorsToIgnore;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		EndLocation,
		LanchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::Type::DoNotTrace,
		ResponseParam,
		ActorsToIgnore,
		true
	);
	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {
	// Work-out different between aimdirection and current barrel rotation.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s BarrelRotator %s"), *AimAsRotator.ToString(), *BarrelRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch); 

	if (DeltaRotator.Yaw > 180) {
		Turret->Rotate(DeltaRotator.Yaw - 360);
	}
	else if(DeltaRotator.Yaw < -180){
		Turret->Rotate(360 - DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;	
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}
