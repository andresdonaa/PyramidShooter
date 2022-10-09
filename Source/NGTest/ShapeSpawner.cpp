
#include "ShapeSpawner.h"

AShapeSpawner::AShapeSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShapeSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AShapeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShapeSpawner::Spawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawned"));
}

void AShapeSpawner::OnSpawnedObjectHitted(ASpawnObject* HittedObject)
{
	UE_LOG(LogTemp, Warning, TEXT("OnSpawnedObjectHitted"));
}


