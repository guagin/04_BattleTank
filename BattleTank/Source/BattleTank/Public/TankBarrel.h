// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), HideCategories=("Physics","Collisio"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float DegreePerSecond);
private:
	UPROPERTY(EditAnyWhere)
	float MaxDegreePerSecond = 20;
	UPROPERTY(EditAnyWhere)
	float MaxElevationDegree = 30.f;
	UPROPERTY(EditAnyWhere)
	float MinElevationDegree = 0.f;
};
