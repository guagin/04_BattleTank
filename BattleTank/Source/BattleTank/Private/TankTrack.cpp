// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"
#include "SprungWheel.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;

}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();
}


void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle) {
	
	auto ForceApplied = CurrentThrottle * TrackMaxDrvingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	TArray<ASprungWheel*> Wheels;

	for (auto child : Children) {
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(child);
		if (!SpawnPoint) {
			continue;
		}
		auto Wheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (!Wheel) {
			continue;
		}
		Wheels.Add(Wheel);
	}
	return Wheels;
}



