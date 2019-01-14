// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp,Warning,TEXT("Get hit."));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	
	
	// calcualte the splippage speed;
	float SplippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work out the required acceleration this fame to correct;
	auto CorrectAcceleration = -SplippageSpeed / (DeltaTime) * GetRightVector();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// calculate and apply sidde way for ( f= ma);
	auto CorrectionForce =(CorrectAcceleration * TankRoot->GetMass())/2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrvingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}