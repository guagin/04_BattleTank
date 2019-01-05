// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	
	// Move the barrel the right amount this frame.
	// Give a max elavation speed, ant the frame time.
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(ClampedElevation,0,0));
}