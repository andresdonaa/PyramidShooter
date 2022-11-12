// Copyright Epic Games, Inc. All Rights Reserved.

#include "NGTestGameMode.h"
#include "NGTestHUD.h"
#include "NGTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ShapeSpawner.h"

ANGTestGameMode::ANGTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANGTestHUD::StaticClass();
}

void ANGTestGameMode::BeginPlay()
{
	GetWorld()->SpawnActor<AShapeSpawner>(SpawnerClass, FVector(-500,0,200), FRotator::ZeroRotator);
}


//if (HasAuthority())
//{
// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s = StringVariable / %f = FloatVariable"), MyString, MyFloat));
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Has Authority"));
//}
//else
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Remote"));
//}
