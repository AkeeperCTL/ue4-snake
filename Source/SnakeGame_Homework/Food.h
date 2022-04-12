// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "Food.generated.h"

class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class SNAKEGAME_HOMEWORK_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

	UFUNCTION(BlueprintCallable)
	void ProcessRotation(float deltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	bool bIsRotatable;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

private:


	void LoadMeshesFromAssets(int MaxMeshesCount);
	void SelectRandomMesh();

	TArray<UStaticMesh*> RandomMeshes;
};
