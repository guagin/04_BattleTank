// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());

	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	UE_LOG(LogTemp, Warning, TEXT("SpawnPoint spawn: %s"), *SpawnedActor->GetName());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
// may return nullptr.
AActor* USpawnPoint::GetSpawnedActor() const
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnPoint spawn: %s"), *SpawnedActor->GetName());
	return SpawnedActor;
}



