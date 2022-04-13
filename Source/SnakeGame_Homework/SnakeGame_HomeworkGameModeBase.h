// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGame_HomeworkGameModeBase.generated.h"

UCLASS()
class SNAKEGAME_HOMEWORK_API ASnakeGame_HomeworkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASnakeGame_HomeworkGameModeBase();

	UFUNCTION(BlueprintNativeEvent)
	void SnakeIsDead();
	void SnakeIsDead_Implementation();

	//UFUNCTION(BlueprintCallable)
	//bool IsInMainMenu();
};

typedef ASnakeGame_HomeworkGameModeBase ASnakeGameMode;
