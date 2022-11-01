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
	
protected:
	
	virtual void BeginPlay() override;
	virtual void Spawn() override;
	
private:

	FVector GetNewRowOffset(float ActorWidth, float ActorHeight);
	void SetSpawnedActorColor(ASpawnObject* SpawnedActor);
	FLinearColor GetRandomColor();
	void MarkActorForDestroy(ASpawnObject* Actor);
	void CheckAdyacentsForDestroy(ASpawnObject* HittedObject);
	void DestroyAllMarkedActors();
	void AddScore();

public:
	virtual void OnSpawnedObjectHitted(ASpawnObject* HittedObject) override;

};
