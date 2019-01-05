// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreePerSecond) {

	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate Called: %f"), DegreePerSecond);
	// Move the barrel the right amount this frame.
	// Give a max elavation speed, ant the frame time.
}