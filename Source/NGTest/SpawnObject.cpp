
#include "SpawnObject.h"
#include "Components/BoxComponent.h"
#include "NGTestProjectile.h"
#include "ShapeSpawner.h"
#include "Net/UnrealNetwork.h"

void ASpawnObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASpawnObject, Color);
}

ASpawnObject::ASpawnObject()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateComponents();
}

void ASpawnObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		ObjectToSpawn->OnComponentHit.AddDynamic(this, &ASpawnObject::OnHitted);
	}

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
	Material->SetVectorParameterValue(FName(TEXT("BaseColor")), Color);
}

void ASpawnObject::OnHitted(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ANGTestProjectile* Projectile = Cast<ANGTestProjectile>(OtherActor);
		if (Projectile)
		{	
			AShapeSpawner* ShapeSpawner = Cast<AShapeSpawner>(GetOwner());
			
			if (Projectile->ControllerInstigator)
			{
				ShapeSpawner->OnSpawnedObjectHitted(this, Projectile->ControllerInstigator);
			}
		}
	}
}