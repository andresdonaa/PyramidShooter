#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (IsLocalPlayerController())
    {
        CreateHUD();
    }
}

void AMyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    ClientShowLeaderboard();
}

void AMyPlayerController::CreateHUD()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();        
    }
}

void AMyPlayerController::ClientShowLeaderboard_Implementation()
{
    TArray<APlayerState*> SortedPlayerStateCollection = SortPlayersStateByScoreDesc();

    ShowLeaderboard(SortedPlayerStateCollection); // BP Function
    SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
}

TArray<APlayerState*> AMyPlayerController::SortPlayersStateByScoreDesc()
{
    UWorld* World = GetWorld();
    TArray<APlayerState*> PlayerStateCollection = World->GetGameState()->PlayerArray;

    PlayerStateCollection.Sort([](const APlayerState& A, const APlayerState& B) { return (A.GetScore() > B.GetScore()); });

    return PlayerStateCollection;
}