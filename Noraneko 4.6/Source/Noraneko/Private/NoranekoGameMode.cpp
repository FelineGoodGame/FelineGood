// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Noraneko.h"
#include "NoranekoGameMode.h"
#include "NoranekoCharacter.h"

ANoranekoGameMode::ANoranekoGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
