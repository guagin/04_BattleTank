// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AminingCompoRef);
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
private:


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
