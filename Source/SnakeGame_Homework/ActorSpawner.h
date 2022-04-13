// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

class UBoxComponent;

UCLASS()
class SNAKEGAME_HOMEWORK_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

	UFUNCTION(BlueprintCallable)
	FVector GetBoundsRandomLocation(const FBoxSphereBounds& Bounds);

	bool IsNearToOtherActor(const FVector& RandomLoc);

	UFUNCTION(BlueprintCallable)
	void SpawnActors(int Count, bool bToRespawn);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ActorsCount;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SpawnedActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
