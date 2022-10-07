
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObject.generated.h"

UCLASS()
class NGTEST_API ASpawnObject : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnObject();
	void ApplyColor();

private:

	void CreateComponents();

protected:
	
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectToSpawn;

	virtual void Tick(float DeltaTime) override;

};
