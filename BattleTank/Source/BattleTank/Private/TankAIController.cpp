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
	if ( AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}

		

}

void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// TODO:subscribe the local method to the tank death event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("%s dead"), *GetName());
	GetPawn()->DetachFromControllerPendingDestroy();
}