// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TrankTrack is used to set maximun driving force, and apply froces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per trank, in Newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrvingForce = 20000000.0f;//  TODO: find a sensible default value.

private:
	UTankTrack();
	void DriveTrack();
	void ApplySidewaysForce();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Hit")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0.f;
};
