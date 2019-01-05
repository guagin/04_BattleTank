// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tank player controller begin play."));
	ATank* Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Tank->GetName()));
	}
	
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair(){
	if(!GetControlledTank()){return;}
	
	FVector HitLocation; //Out Parameter.

	if (GetSightRayHitLocation(HitLocation)) {// has side effect. is going to line trace.
		GetControlledTank()->AimAt(HitLocation);
	}

}

// get world location of linetrace through corsshair, true if hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const {
	// Find the crosshair position in pixel coordinates.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector CameraWorldDirection;
	if (GetLookDirection(ScreenLocation, CameraWorldDirection)) {
		FHitResult HitResult;
		if (GetLookVectorHitLocation(CameraWorldDirection, HitResult)) {
			HitLocation = HitResult.Location;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("aiming is missing"));
		}
	}
	
	
	// Line-Tace along that look direction, and see what we hit( up to max range).

	return true;
}

// De-poject the screen projection of corsshair to a world direction.
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldDirection) const{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		CameraWorldDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction,FHitResult& HitResult) const{
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End =  Start + (LineTraceRange * Direction);

	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(
		EName::NAME_None,
		false,	
		GetControlledTank()
	);

	return GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParams
	);
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}