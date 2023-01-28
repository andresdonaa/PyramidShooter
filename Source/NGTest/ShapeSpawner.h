#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShapeSpawner.generated.h"

UCLASS()
class NGTEST_API AShapeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	//Constructor	
	AShapeSpawner();

protected: //Fields
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpawnObject> SpawnObjectClass;

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> SpawnColors;

	UPROPERTY()
	int SpawnedObjectCounter = 0;

protected: //Functions
	virtual void BeginPlay() override;
	virtual void Spawn();

public:	//Functions
	virtual void Tick(float DeltaTime) override;
	virtual void OnSpawnedObjectHitted(ASpawnObject* HittedObject, AController* HitterOwner);
};
