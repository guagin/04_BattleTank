// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float) override;
private:
	
	ATank* GetControlledTank() const;
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
	bool GetLookDirection(FVector2D, OUT FVector&) const;
	bool GetLookVectorHitLocation(FVector, OUT FHitResult&) const;

	UPROPERTY(EditAnyWhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnyWhere)
	float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditAnyWhere)
	float LineTraceRange = 1000000.f;
};
