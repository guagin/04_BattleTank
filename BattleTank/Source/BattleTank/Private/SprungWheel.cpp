// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// to create the same hierarchy to them blueprint one.

	Srping = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Srping"));
	SetRootComponent(Srping);
	

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetupAttachment(Srping);


	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Srping);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay() {
	Super::BeginPlay();
	auto parent = GetAttachParentActor();
	if (parent) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *parent->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("null"));
	}

	
}
// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

