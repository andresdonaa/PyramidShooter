#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (IsLocalPlayerController())
    {
        CreateHUD();
    }
}

void AMyPlayerController::CreateHUD()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();        
    }
}

void AMyPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    ClientShowLeaderboard();
}

void AMyPlayerController::ClientShowLeaderboard_Implementation()
{
    ShowLeaderboard(); // BP Function
    SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
}