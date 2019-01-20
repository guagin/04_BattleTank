// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * Responsilbe for helper the player aim.
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Event")
	void OnTankDeath();

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float AcceptanceRadius = 10000;
	UTankAimingComponent* AimingComponent = nullptr;
	ATank* Tank;
};
