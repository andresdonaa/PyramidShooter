
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObject.generated.h"

UCLASS()
class NGTEST_API ASpawnObject : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectToSpawn;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	FLinearColor Color;

	UPROPERTY()
	class UMaterialInstanceDynamic* Material;

public:	

	ASpawnObject();
	void ApplyColor(FLinearColor ColorToApply);

private:
	
	void CreateComponents();
	void ApplyDefaultColor();

protected:
	
	virtual void BeginPlay() override;
};
