
#include "SpawnObject.h"
#include "Components/BoxComponent.h"
#include "NGTestProjectile.h"
#include "ShapeSpawner.h"


ASpawnObject::ASpawnObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateComponents();
}

void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();
	
	ObjectToSpawn->OnComponentHit.AddDynamic(this, &ASpawnObject::OnHitted);

	ApplyDefaultColor();
}

void ASpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnObject::CreateComponents()
{	
	ObjectToSpawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor"));
	
	RootComponent = ObjectToSpawn;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->SetupAttachment(ObjectToSpawn);
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

void ASpawnObject::OnHitted(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (Cast<ANGTestProjectile>(OtherActor))
		{
			AShapeSpawner* ShapeSpawner = Cast<AShapeSpawner>(GetOwner());

			ShapeSpawner->OnSpawnedObjectHitted(this);
		}
	}
}
