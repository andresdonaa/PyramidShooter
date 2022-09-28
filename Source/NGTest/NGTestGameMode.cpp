// Copyright Epic Games, Inc. All Rights Reserved.

#include "NGTestGameMode.h"
#include "NGTestHUD.h"
#include "NGTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANGTestGameMode::ANGTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANGTestHUD::StaticClass();
}
