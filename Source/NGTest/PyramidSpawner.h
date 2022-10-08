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
	
protected:
	
	virtual void BeginPlay() override;
	void Spawn();

private:

	FVector GetNewRowOffset(float ActorWidth, float ActorHeight);
	void SetSpawnedActorColor(ASpawnObject* SpawnedActor);
	FLinearColor GetRandomColor();
};
