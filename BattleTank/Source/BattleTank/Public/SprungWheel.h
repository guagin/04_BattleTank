// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"


class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	void AddDrivingForce(float ForceMagnitude);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnyWhere, Category="Components")
	UPhysicsConstraintComponent* Spring = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};
