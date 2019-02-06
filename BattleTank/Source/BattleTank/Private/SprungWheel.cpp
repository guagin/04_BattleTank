// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
ASprungWheel::ASprungWheel()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	// to create the same hierarchy to them blueprint one.
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Srping"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(Spring);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraints"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	/*Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);*/
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay() {
	Super::BeginPlay();
	SetupConstraint();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
}

void ASprungWheel::SetupConstraint() {
	auto parent = GetAttachParentActor();
	if (!parent) {
		return;
	}

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(parent->GetRootComponent());
	if (!BodyRoot) { return; }
	Spring->SetConstrainedComponents(
		BodyRoot,
		NAME_None,
		Axle,
		NAME_None
	);
	AxleWheelConstraint->SetConstrainedComponents(
		Axle,
		NAME_None,
		Wheel,
		NAME_None
	);
}
void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
	auto force = Axle->GetForwardVector() * TotalForceMagnitudeThisFrame;
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		TotalForceMagnitudeThisFrame = 0;
		
	}
}

