// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Yaw + RotationChange;
	auto TankName = GetOwner()->GetName();
	SetRelativeRotation(FRotator(0, RawRotation, 0));
}