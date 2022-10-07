
#include "PyramidSpawner.h"
#include "ShapeSpawner.h"
#include "SpawnObject.h"


void APyramidSpawner::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}


void APyramidSpawner::Spawn()
{
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
			AActor* SpawnedActor = nullptr;

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
		}

		LastSpawnPosition = InitialRowSpawnPosition + GetNewRowOffset(ActorWidth, ActorHeight);
		InitialRowSpawnPosition += GetNewRowOffset(ActorWidth, ActorHeight);
	}
}

FVector APyramidSpawner::GetNewRowOffset(float ActorWidth, float ActorHeight)
{
	return FVector((ActorWidth / 2) + (ColumnSpawnOffset / 2), 0, ActorHeight + 10);
}

