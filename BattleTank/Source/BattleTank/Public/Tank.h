// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Delaration.
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100.f;

	UPROPERTY(VisibleAnyWhere, Category = "Health")
	float CurrentHealth = StartingHealth;

	ATank();
};

