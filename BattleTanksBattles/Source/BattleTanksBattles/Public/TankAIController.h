// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANKSBATTLES_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void SetPawn(APawn* InPawn) override;

protected:
	//radius for player to be in so that ai stops 6000cm = 60m
	UPROPERTY(EditDefaultsOnly, Category = "setup")
	float stopRadius = 6000.0f;

	ATank* possesedTank = nullptr;

private:
	UFUNCTION()
	void OnTankDeath();
};
