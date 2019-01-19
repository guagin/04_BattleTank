// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	const float DamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	float DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s take damage amount: %f, dmage to apply: %f health: %f"), *GetName(), DamageAmount, DamageToApply, CurrentHealth);
	CurrentHealth -= DamageToApply;
	return DamageToApply;
}


