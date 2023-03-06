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
    DisablePlayerMovement();
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
    TArray<APlayerState*> SortedPlayerStateCollection = GetSortedPlayersStateByScoreDesc();
    ShowLeaderboard(SortedPlayerStateCollection); // BP Function
}

void AMyPlayerController::DisablePlayerMovement_Implementation()
{
    SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
    SetIgnoreMoveInput(true);
}

TArray<APlayerState*> AMyPlayerController::GetSortedPlayersStateByScoreDesc()
{
    UWorld* World = GetWorld();
    TArray<APlayerState*> PlayerStateCollection = World->GetGameState()->PlayerArray;

    PlayerStateCollection.Sort([](const APlayerState& A, const APlayerState& B) { return (A.GetScore() > B.GetScore()); });

    return PlayerStateCollection;
}