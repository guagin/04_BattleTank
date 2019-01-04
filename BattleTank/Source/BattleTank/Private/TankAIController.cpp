// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();

	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s respawn."), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cant get any tank."));
	}
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank: %s ."), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cant get any player tank."));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cant get any player tank."));
	}
		
}

ATank * ATankAIController::GetPlayerTank() const {
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (PlayerPawn) {
		return Cast<ATank>(PlayerPawn);
	}
	else {
		return nullptr;
	}
}
