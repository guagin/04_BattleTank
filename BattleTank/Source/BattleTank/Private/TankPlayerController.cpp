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
	UE_LOG(LogTemp, Warning, TEXT("player controller tick:%f"), DeltaTime);
	//AimTowardCorsshair.
}

void ATankPlayerController::AimTowardCorsshair(){
	if(!GetControlledTank()){return;}

	// get world location linetrace through corsshair.
	// if it hits the landscap
			// tell controlled tank to aim this point.
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}