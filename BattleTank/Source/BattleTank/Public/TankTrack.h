// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"
class ASprungWheel;
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
	void DriveTrack(float CurrentThrottle);
	
	virtual void BeginPlay() override;

	TArray<ASprungWheel*> GetWheels() const;

};
