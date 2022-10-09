
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
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectToSpawn;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	FLinearColor Color;

	UPROPERTY()
	bool bShouldDestroy = false;

	UPROPERTY()
	class UMaterialInstanceDynamic* Material;

public:	

	ASpawnObject();
	void ApplyColor(FLinearColor ColorToApply);

	UFUNCTION()
	void OnHitted(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	
	void CreateComponents();
	void ApplyDefaultColor();

protected:
	
	virtual void BeginPlay() override;
};
