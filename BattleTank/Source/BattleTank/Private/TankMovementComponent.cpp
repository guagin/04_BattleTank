// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack2Set, UTankTrack* RightTrack2Set) {
	if (!ensure(LeftTrack2Set || RightTrack2Set)) { return; }
	LeftTrack = LeftTrack2Set;
	RightTrack = RightTrack2Set;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIFowardIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(TankFoward, AIFowardIntention);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(TankFoward, AIFowardIntention).Z;

	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack) && !ensure(RightTrack)) { return; }
	if (Throw == 0.f) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack) &&  !ensure(RightTrack)) { return; }
	if (Throw == 0.f) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}