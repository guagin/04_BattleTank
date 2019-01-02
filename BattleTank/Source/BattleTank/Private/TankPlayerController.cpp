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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));
		// get world location linetrace through corsshair.
		// if it hits the landscap
				// tell controlled tank to aim this point.
	}

}

// get world location of linetrace through corsshair, true if hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const {
	HitLocation.X = 100.f;
	//FVector location = GetPawn()->GetActorLocation();
	//// maybe get the rotation from camera?
	//FRotator ratator = GetPawn()->
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}