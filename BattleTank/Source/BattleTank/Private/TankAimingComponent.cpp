// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/GameplayStaticsTypes.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankAimingComponent::BeginPlay(){
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if (GetAmmo() == 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if (!isReloaded()) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const{
	if(!ensure(Barrel)){return false;}
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !AimDirection.Equals(BarrelForwardVector, 0.1);
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	if (!BarrelToSet || !TurretToSet) { 
	}
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


EFiringStatus UTankAimingComponent::GetFiringStatus() const {
	return FiringStatus;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) {
		return; 
	}
	if (!ensure(Turret)) {
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
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::Type::DoNotTrace,
		ResponseParam,
		ActorsToIgnore,
		false
	);
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

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


void UTankAimingComponent::Fire() {

	if (!ensure(Barrel)) { return; }

	if (FiringStatus == EFiringStatus::Locked) {
		// Spawn a projectile at the socket location of barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		FiringStatus = EFiringStatus::Reloading;
		Ammo-=1;
	}
}

int32 UTankAimingComponent::GetAmmo() const{
	return Ammo;
}

bool UTankAimingComponent::isReloaded() const {
	return (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
}