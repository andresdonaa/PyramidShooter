#pragma once

#include "CoreMinimal.h"
#include "ShapeSpawner.h"
#include "PyramidSpawner.generated.h"

UCLASS()
class NGTEST_API APyramidSpawner : public AShapeSpawner
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	int PyramidBaseColumns = 7;

	UPROPERTY()
	int ColumnSpawnOffset;

	UPROPERTY()
	TArray<AActor*> ActorsMarkedForDestroy;

	UPROPERTY()
	TArray<int> MatchingOverlappingCollection;
	
	//TODO: Move to specific responsible class
	const TArray<int> FibonacciSeries = { 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181 };


protected:
	
	virtual void BeginPlay() override;
	virtual void Spawn() override;

private:

	FVector GetNewRowOffset(float ActorWidth, float ActorHeight);
	void SetSpawnedActorColor(ASpawnObject* SpawnedActor);
	FLinearColor GetRandomColor();
	void MarkActorForDestroy(ASpawnObject* Actor);
	void CheckAdyacentsForDestroy(ASpawnObject* HittedObject);
	void DestroyAllMarkedActors(AController* HitterOwner);
	void AddScore(AController* HitterOwner);
	void SpawnActors(UWorld* World, FVector& LastSpawnPosition, FVector& SpawnOffset, FVector& InitialRowSpawnPosition, float ActorWidth, float ActorHeight);
	void CheckForGameOver();
	void EndGame();
	void FillMatchingOverlappingCollection(TArray<AActor*> OverlappingActors, FLinearColor ColorToCompare);

public:
	virtual void OnSpawnedObjectHitted(ASpawnObject* HittedObject, AController* HitterOwner) override;
};
