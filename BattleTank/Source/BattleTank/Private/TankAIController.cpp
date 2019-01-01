// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	ATank* Tank = GetControlledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s respawn."), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cant get any tank."));
	}
	

}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}