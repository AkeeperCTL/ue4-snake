// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.0f;
	MovementSpeed = 10.0f;
	LastMoveDirection = EMovementDirection::UP;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();	
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);

}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewElementLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewElementTransform(NewElementLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewElementTransform);

		NewSnakeElement->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		SnakeElements.Add(NewSnakeElement);
	}
}

void ASnakeBase::Move(float deltatime)
{
	FVector MovementVector(0,0,0);
	float MovementSpeedDelta = MovementSpeed * deltatime;

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
	}

	AddActorWorldOffset(MovementVector);
}

