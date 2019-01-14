// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	
	// Drive the tracks
	// Apply Sideways force.
	
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce() {
	// calcualte the splippage speed;
	float SplippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->DeltaTimeSeconds;
	// work out the required acceleration this fame to correct;
	auto CorrectAcceleration = -SplippageSpeed / (DeltaTime)* GetRightVector();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// calculate and apply sidde way for ( f= ma);
	auto CorrectionForce = (CorrectAcceleration * TankRoot->GetMass()) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
}

void UTankTrack::DriveTrack() {
	
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrvingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}