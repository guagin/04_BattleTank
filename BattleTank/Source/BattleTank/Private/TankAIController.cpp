// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<ATank>(GetPawn());
	AimingComponent = Tank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!ensure(PlayerTank)) {
		return;
	}
	if (!ensure(AimingComponent)) {
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius); 
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
		
}