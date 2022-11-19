
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class NGTEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	
	void CreateHUD();

	UFUNCTION(Reliable, Client)
	void ClientShowLeaderboard();

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowLeaderboard();

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* HUD;

};
