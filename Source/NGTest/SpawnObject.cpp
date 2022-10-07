// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObject.h"

// Sets default values
ASpawnObject::ASpawnObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateComponents();
}

void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnObject::CreateComponents()
{
	ObjectToSpawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor"));
	ObjectToSpawn->SetupAttachment(RootComponent);
	
}

void ASpawnObject::ApplyColor()
{
}
