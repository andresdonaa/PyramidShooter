
#include "PyramidSpawner.h"
#include "ShapeSpawner.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"


void APyramidSpawner::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

void APyramidSpawner::Spawn()
{
	Super::Spawn();

	UWorld* World = GetWorld();

	ASpawnObject* ReferenceActor = World->SpawnActor<ASpawnObject>(SpawnObjectClass, GetActorLocation() + 1000, GetActorRotation());
	FVector ActorMeshSize = ReferenceActor->ObjectToSpawn->GetStaticMesh()->GetBounds().GetBox().GetSize();

	float ActorWidth = ActorMeshSize.X;
	float ActorHeight = ActorMeshSize.Z;
	ColumnSpawnOffset = ActorWidth * 0.2f; // 20% of actor's width

	float XSpawnPoint = ActorWidth + ColumnSpawnOffset;

	FVector SpawnOffset = FVector(XSpawnPoint, 0, 0);
	FVector LastSpawnPosition = GetActorLocation();
	FVector InitialRowSpawnPosition = GetActorLocation();

	ReferenceActor->Destroy();

	for (int row = 0; row < PyramidBaseColumns; row++)
	{
		bool isFirstColumnInRow = true;

		for (int col = 0; col < PyramidBaseColumns - row; col++)
		{
			ASpawnObject* SpawnedActor = nullptr;

			if (!isFirstColumnInRow)
			{
				SpawnedActor = World->SpawnActor<ASpawnObject>(SpawnObjectClass, LastSpawnPosition + SpawnOffset, GetActorRotation());
			}
			else
			{
				SpawnedActor = World->SpawnActor<ASpawnObject>(SpawnObjectClass, LastSpawnPosition, GetActorRotation());
				isFirstColumnInRow = false;
			}

			LastSpawnPosition = SpawnedActor->GetActorLocation();

			SetSpawnedActorColor(SpawnedActor);
			SpawnedActor->SetOwner(this);
		}

		LastSpawnPosition = InitialRowSpawnPosition + GetNewRowOffset(ActorWidth, ActorHeight);
		InitialRowSpawnPosition += GetNewRowOffset(ActorWidth, ActorHeight);
	}
}

FVector APyramidSpawner::GetNewRowOffset(float ActorWidth, float ActorHeight)
{
	return FVector((ActorWidth / 2) + (ColumnSpawnOffset / 2), 0, ActorHeight + 10);
}

void APyramidSpawner::SetSpawnedActorColor(ASpawnObject* SpawnedActor)
{
	FLinearColor RandomColor = GetRandomColor();
	SpawnedActor->ApplyColor(RandomColor);
}

FLinearColor APyramidSpawner::GetRandomColor()
{
	int ColorsLength = SpawnColors.Num();
	int RandomIndex = FMath::RandRange(0, ColorsLength - 1);
	return SpawnColors[RandomIndex];
}

void APyramidSpawner::OnSpawnedObjectHitted(ASpawnObject* HittedObject)
{
	Super::OnSpawnedObjectHitted(HittedObject);

	UGameplayStatics::GetPlayerPawn(this, 0)->GetController()->GetPlayerState<APlayerState>()->Score++;

	PrintOvelappingActorsName(HittedObject);
}

void APyramidSpawner::PrintOvelappingActorsName(ASpawnObject* OfActor)
{
	TArray<AActor*> OverlappingActors;
	OfActor->GetOverlappingActors(OverlappingActors, OfActor->StaticClass());

	UE_LOG(LogTemp, Warning, TEXT("Ovelapping Actors COUNT: %d"), OverlappingActors.Num());

	for (AActor* actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ovelapping Actors: %s"), *actor->GetFName().ToString());
	}
}