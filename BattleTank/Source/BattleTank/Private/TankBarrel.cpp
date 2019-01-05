// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float ReletiveSpeed) {
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("time: %f Barrel->Elevate Called: %f"), Time, ReletiveSpeed);
	// Move the barrel the right amount this frame.
	// Give a max elavation speed, ant the frame time.
}