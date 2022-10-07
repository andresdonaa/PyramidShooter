
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
}


