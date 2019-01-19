// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UPROPERTY(EditAnyWhere)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnyWhere, Category="Component")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnyWhere, Category="Component")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
	URadialForceComponent* ExplosionForce = nullptr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	
	void LaunchProjectile(float Speed);
private:
	UFUNCTION(BlueprintCallable, Category = "Hit")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 20.f;

	void OnTimerExpired();
};
