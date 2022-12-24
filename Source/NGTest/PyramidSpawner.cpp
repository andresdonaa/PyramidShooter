
#include "PyramidSpawner.h"
#include "ShapeSpawner.h"
#include "SpawnObject.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"

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

	SpawnActors(World, LastSpawnPosition, SpawnOffset, InitialRowSpawnPosition, ActorWidth, ActorHeight);
}

void APyramidSpawner::SpawnActors(UWorld* World, FVector& LastSpawnPosition, FVector& SpawnOffset, FVector& InitialRowSpawnPosition, float ActorWidth, float ActorHeight)
{
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

			SpawnedObjectCounter++;

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

void APyramidSpawner::OnSpawnedObjectHitted(ASpawnObject* HittedObject, AController* HitterOwner)
{
	Super::OnSpawnedObjectHitted(HittedObject, HitterOwner);

	MarkActorForDestroy(HittedObject);

	CheckAdyacentsForDestroy(HittedObject);

	DestroyAllMarkedActors(HitterOwner);

	CheckForGameOver();	
}

void APyramidSpawner::CheckAdyacentsForDestroy(ASpawnObject* FromActor)
{
	TArray<AActor*> OverlappingActors;
	FromActor->GetOverlappingActors(OverlappingActors, FromActor->StaticClass());
	FLinearColor ColorToCompare = FromActor->Color;
	
	FillMatchingOverlappingCollection(OverlappingActors, ColorToCompare);

	for (AActor* actor : OverlappingActors)
	{
		ASpawnObject* AdyacentActor = Cast<ASpawnObject>(actor);
		if (AdyacentActor)
		{
			if (AdyacentActor->Color == ColorToCompare && !AdyacentActor->bShouldDestroy)
			{
				MarkActorForDestroy(AdyacentActor);
				CheckAdyacentsForDestroy(AdyacentActor);
			}
		}
	}
}

void APyramidSpawner::FillMatchingOverlappingCollection(TArray<AActor*> OverlappingActors, FLinearColor ColorToCompare)
{
	int OverlappingMatchCount = 0;
	for (AActor* actor : OverlappingActors)
	{
		ASpawnObject* AdyacentActor = Cast<ASpawnObject>(actor);
		if (AdyacentActor)
		{
			if (!AdyacentActor->bAlreadyMatchCounted && AdyacentActor->Color == ColorToCompare && !AdyacentActor->bShouldDestroy)
			{
				OverlappingMatchCount++;
				AdyacentActor->bAlreadyMatchCounted = true;
			}
		}
	}

	if (OverlappingMatchCount > 0)
	{
		MatchingOverlappingCollection.Add(OverlappingMatchCount);
	}
}

void APyramidSpawner::MarkActorForDestroy(ASpawnObject* Actor)
{
	Actor->bShouldDestroy = true;

	ActorsMarkedForDestroy.Add(Actor);
}

void APyramidSpawner::DestroyAllMarkedActors(AController* HitterOwner)
{
	AddScore(HitterOwner);

	for (AActor* actor : ActorsMarkedForDestroy)
	{
		actor->Destroy();
		SpawnedObjectCounter--;
	}
	
	ActorsMarkedForDestroy.Empty();
}

void APyramidSpawner::CheckForGameOver()
{
	if (SpawnedObjectCounter <= 0)
	{
		EndGame();
	}
}

void APyramidSpawner::EndGame()
{
	for (FConstControllerIterator ControllerIterator = GetWorld()->GetControllerIterator(); ControllerIterator; ++ControllerIterator)
	{
		(*ControllerIterator)->GameHasEnded(NULL, false);
	}
}

void APyramidSpawner::AddScore(AController* HitterOwner)
{	
	if (HitterOwner)
	{
		int fibonacciScoreResult = FibonacciSeries[1];

		for (int i = 0; i < MatchingOverlappingCollection.Num(); i++)
		{
			fibonacciScoreResult += MatchingOverlappingCollection[i] * FibonacciSeries[i + 2];
		}

		APlayerState* PlayerState = HitterOwner->GetPlayerState<APlayerState>();
		int ResultingScore = fibonacciScoreResult + PlayerState->Score++;

		PlayerState->SetScore(ResultingScore);

		MatchingOverlappingCollection.Empty();
	}
}

