// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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
		//UE_LOG(LogTemp, Warning, TEXT("look direction: %s"), *(HitLocation.ToString()));
		// get world location linetrace through corsshair.
		// if it hits the landscap
				// tell controlled tank to aim this point.
	}

}

// get world location of linetrace through corsshair, true if hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const {
	HitLocation.X = 100.f;
	// Find the crosshair position in pixel coordinates.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Screen location:%s"), *(ScreenLocation.ToString()));
	FVector CameraWorldDirection;
	if (GetLookDirection(ScreenLocation, CameraWorldDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("CameraWorldDirection :%s"), *(CameraWorldDirection.ToString()));
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

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}