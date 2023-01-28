
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class NGTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private: //Fields
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

public: //Fields
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HUD;

protected:
	virtual void BeginPlay() override;

public: //Functions
	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowLeaderboard(const TArray<class APlayerState*>& PlayerStateCollection);

private: //Functions
	UFUNCTION(Reliable, Client)
	void ClientShowLeaderboard();

	void CreateHUD();

	TArray<APlayerState*> SortPlayersStateByScoreDesc();
};
