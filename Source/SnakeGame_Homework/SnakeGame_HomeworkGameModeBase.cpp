// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGame_HomeworkGameModeBase.h"

ASnakeGame_HomeworkGameModeBase::ASnakeGame_HomeworkGameModeBase()
{
	SnakeGameScore, LastSnakeGameScore = 0;
}


void ASnakeGame_HomeworkGameModeBase::SnakeIsDead_Implementation()
{
	LastSnakeGameScore = SnakeGameScore;
}

//
//bool ASnakeGame_HomeworkGameModeBase::IsInMainMenu()
//{
//	if (GetWorld()->GetName() == FString(TEXT("Main_Menu")))
//		return;
//}
