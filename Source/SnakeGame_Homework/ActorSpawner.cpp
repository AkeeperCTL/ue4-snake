// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"
#include "Components/BoxComponent.h"
#include "SnakeGame_HomeworkGameModeBase.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetBoxExtent(FVector(400, 400, 70));
	ActorsCount = 0;
}

FVector AActorSpawner::GetBoundsRandomLocation(const FBoxSphereBounds& Bounds)
{
	FBoxSphereBounds BoxBounds = Bounds;

	float BoundsX = BoxBounds.BoxExtent.X;
	float BoundsY = BoxBounds.BoxExtent.Y;

	float RandomX = FMath::RandRange(-BoundsX, BoundsX);
	float RandomY = FMath::RandRange(-BoundsY, BoundsY);

	FVector RandomLocation(RandomX, RandomY, BoxBounds.Origin.Z);

	if (IsNearToOtherActor(RandomLocation))
		GetBoundsRandomLocation(Bounds);
	
	return RandomLocation;
}

bool AActorSpawner::IsNearToOtherActor(const FVector& RandomLoc)
{
	if (SpawnedActors.Num() > 0)
	{
		for (AActor* Actor : SpawnedActors)
		{
			if (IsValid(Actor))
			{
				FVector ActorLocation = Actor->GetActorLocation();

				float ActorDistance = (ActorLocation - RandomLoc).Size();
				float CheckDistance = 300.0f;

				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("ActorDistance: %f, is true %d"),
				//	ActorDistance, int32(ActorDistance < CheckDistance)));

				return  ActorDistance < CheckDistance;
			}
		}
	}
	return false;
}

void AActorSpawner::SpawnActors(int Count, bool bToRespawn)
{
	if (bToRespawn)
	{
		for (AActor* Actor : SpawnedActors)
		{
			if (IsValid(Actor))
				Actor->Destroy();
		}
	}

	if (SpawnedActors.Num() == 0)
	{
		for (int i = 0; i < Count;)
		{
			FVector RandomLocation = GetBoundsRandomLocation(BoxComponent->Bounds);
			FTransform RandomTransform(RandomLocation);

			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, RandomTransform);

			if (IsValid(SpawnedActor))
			{
				SpawnedActors.AddUnique(SpawnedActor);
				i++;
			}
		}
	}
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnActors(ActorsCount, false);
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Undefined behaviour
	/*for (AActor* Actor : SpawnedActors)
	{
		if (!IsValid(Actor))
		{
			SpawnedActors.Remove(Actor);
		}	
	}*/

	for (int i = 0; i < SpawnedActors.Num(); i++)
	{
		AActor* Actor = SpawnedActors[i];
		if (!IsValid(Actor))
			SpawnedActors.Remove(Actor);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("SpawnedActors: %d"), SpawnedActors.Num()));
}