// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 50.0f;
	ElementsCount = 6;
	MovementSpeed = 0.5f;
	LastMoveDirection = EMovementDirection::UP;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	AddSnakeElement(ElementsCount);
	SetActorTickInterval(MovementSpeed);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProcessMovement();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewElementLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewElementTransform(GetActorLocation() - NewElementLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewElementTransform);

		NewSnakeElement->SnakeOwner = this;

		int32 ElemIndex = SnakeElements.Add(NewSnakeElement);
		if (ElemIndex == 0)
			NewSnakeElement->SetFirstElementType();
	}
}

void ASnakeBase::ProcessMovement()
{
	FVector MovementVector(0,0,0);
	float MovementSpeedDelta = ElementSize;

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MovementSpeedDelta;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeedDelta;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeedDelta;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeedDelta;
		break;
	default:
		break;
	}

	//AddActorWorldOffset(MovementVector);

	for (int i = SnakeElements.Num() - 1; i > 0; --i)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];

		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex = 0;
		SnakeElements.Find(OverlappedElement, ElemIndex);

		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);

		if (InteractableInterface)
		{
			InteractableInterface->Interact(Other, bIsFirst);
		}
	}
}

