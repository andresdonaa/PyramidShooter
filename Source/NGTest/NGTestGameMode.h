// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NGTestGameMode.generated.h"

UCLASS(minimalapi)
class ANGTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public: //Constructor
	ANGTestGameMode();

private: //Fields
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AShapeSpawner> SpawnerClass;

protected:
	virtual void BeginPlay() override;
};



