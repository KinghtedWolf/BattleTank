// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurret.generated.h"

/**
 * Rotates the turret
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKSBATTLES_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//makes the turret yaw used in aiming component
	void yaw(float reletiveSpeed);
	
private:
	//how fast the turret rotates
	UPROPERTY(EditDefaultsOnly, Category = "TurretSetup")
	float maxDegreesPerSecond = 20.0f;
	
};
