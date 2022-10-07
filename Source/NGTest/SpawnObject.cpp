
#include "SpawnObject.h"

ASpawnObject::ASpawnObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateComponents();
}

void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();

	ApplyDefaultColor();
}

void ASpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnObject::CreateComponents()
{
	ObjectToSpawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor"));
	ObjectToSpawn->SetupAttachment(RootComponent);
}

void ASpawnObject::ApplyDefaultColor()
{
	Material = UMaterialInstanceDynamic::Create(ObjectToSpawn->GetMaterial(0), NULL);
	ObjectToSpawn->SetMaterial(0, Material);
	Material->SetVectorParameterValue(FName(TEXT("BaseColor")), Color);
}

void ASpawnObject::ApplyColor(FLinearColor ColorToApply)
{
	Color = ColorToApply;
	Material->SetVectorParameterValue(FName(TEXT("BaseColor")), ColorToApply);
}