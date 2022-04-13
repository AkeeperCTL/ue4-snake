// Fill out your copyright notice in the Description page of Project Settings.


#include "Fence.h"
#include "SnakeBase.h"

// Sets default values
AFence::AFence()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AFence::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFence::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
			Snake->Destroy();
	}
}