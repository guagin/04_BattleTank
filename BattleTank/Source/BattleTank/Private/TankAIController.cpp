// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto Tank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		Tank->AimAt(PlayerTank->GetActorLocation());
		Tank->Fire(); // TODO: dont fire every frame.
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cant get any player tank."));
	}
		
}