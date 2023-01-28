
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObject.generated.h"

UCLASS()
class NGTEST_API ASpawnObject : public AActor
{
	GENERATED_BODY()
	
private: //Fields
	UPROPERTY()
	class UMaterialInstanceDynamic* Material;

public:	//Fields
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectToSpawn;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DestructionParticleEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* DestructionSFX;

	UPROPERTY(Replicated, EditAnywhere)
	FLinearColor Color;

	UPROPERTY()
	bool bShouldDestroy = false;

	UPROPERTY()
	bool bAlreadyMatchCounted = false;

public: //Functions
	virtual void Tick(float DeltaTime) override;
	ASpawnObject();
	void ApplyColor(FLinearColor ColorToApply);

	UFUNCTION()
	void OnHitted(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private: //Functions	
	void CreateComponents();
	void ApplyDefaultColor();
};
