#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShapeSpawner.generated.h"

UCLASS()
class NGTEST_API AShapeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AShapeSpawner();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpawnObject> SpawnObjectClass;

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> SpawnColors;

	virtual void BeginPlay() override;

	virtual void Spawn();

public:	

	virtual void Tick(float DeltaTime) override;
	virtual void OnSpawnedObjectHitted(ASpawnObject* HittedObject);

};
