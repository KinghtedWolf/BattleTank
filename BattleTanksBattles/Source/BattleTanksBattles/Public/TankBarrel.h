// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

/**
 * used to elevate the barrel by a certain ammount up and down
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKSBATTLES_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//reletiveSpeed is between -1 and +1 min or max
	void Elevate(float reletiveSpeed);
	
private:
	//how fast the barrel elevates
	UPROPERTY(EditDefaultsOnly, Category =  "BarrelSetup")
	float maxDegreesPerSecond = 20.0f;

	//how high the barrel can go
	UPROPERTY(EditDefaultsOnly, Category = "BarrelSetup")
	float maxElevation = 35.0f;

	//how low the barrel can go
	UPROPERTY(EditDefaultsOnly, Category = "BarrelSetup")
	float minElevation = 0.0f;

};
