
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObject.generated.h"

UCLASS()
class NGTEST_API ASpawnObject : public AActor
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHitted(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	UPROPERTY()
	class UMaterialInstanceDynamic* Material;

public:	

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

	ASpawnObject();
	void ApplyColor(FLinearColor ColorToApply);


private:
	
	void CreateComponents();
	void ApplyDefaultColor();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

};
