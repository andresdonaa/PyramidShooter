#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
   /* if (IsLocalPlayerController())
    {
        CreateHUD();
    }*/
}

void AMyPlayerController::CreateHUD()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

