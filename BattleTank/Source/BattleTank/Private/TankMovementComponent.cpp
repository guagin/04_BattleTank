// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack2Set, UTankTrack* RightTrack2Set) {
	if (!LeftTrack2Set || !RightTrack2Set) { return; }
	LeftTrack = LeftTrack2Set;
	RightTrack = RightTrack2Set;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward Throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}
