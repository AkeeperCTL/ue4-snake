// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"

#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Runtime/Engine/Public/EngineGlobals.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh"));
	RootComponent = MeshComponent;

	bIsRotatable = true;
	RotationSpeed = 100.0f;

	LoadMeshesFromAssets(3);
}

void AFood::ProcessRotation(float deltaTime)
{
	if (!bIsRotatable)
		return;

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += deltaTime * RotationSpeed;

	SetActorRotation(CurrentRotation);
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	SelectRandomMesh();
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessRotation(DeltaTime);
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);

		if (IsValid(Snake))
		{
			Snake->AddSnakeElement(1);
			Destroy();
		}
	}
}

void AFood::LoadMeshesFromAssets(int MaxMeshesCount)
{
	for (int i = 0; i < MaxMeshesCount; i++)
	{
		FName MeshPath = "";
		switch (i)
		{
		case 0:
			MeshPath = TEXT("/Game/Meshes/Food/SM_Item_Fruit_01.SM_Item_Fruit_01");
			break;
		case 1:
			MeshPath = TEXT("/Game/Meshes/Food/SM_Item_Fruit_02.SM_Item_Fruit_02");
			break;
		case 2:
			MeshPath = TEXT("/Game/Meshes/Food/SM_Item_Fruit_03.SM_Item_Fruit_03");
			break;
		}

		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(*MeshPath.ToString());

		if (MeshAsset.Succeeded())
			RandomMeshes.Add(MeshAsset.Object);
	}
}

void AFood::SelectRandomMesh()
{
	int RandomNumber = FMath::RandRange(0, RandomMeshes.Num() - 1);
	UStaticMesh* RandomMesh = RandomMeshes[RandomNumber];

	if (IsValid(RandomMesh))
	{
		MeshComponent->SetStaticMesh(RandomMesh);
		MeshComponent->SetWorldScale3D(FVector(2, 2, 2));
		MeshComponent->SetMaterial(0,RandomMesh->GetMaterial(0));
	}
}