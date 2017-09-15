// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANKSBATTLES_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void SetPawn(APawn * InPawn);

	//the crosshairs location on screen
	void  aimToCrossHair();

	UFUNCTION(BlueprintImplementableEvent = Category = "Setup")
	void foundAimingComponent(UTankAimingComponent* aimingCompRef);

public:
	//the crosshairs location on screen
	UPROPERTY(EditDefaultsOnly)
	float crossHairX = 0.5;

	//the crosshairs location on screen
	UPROPERTY(EditDefaultsOnly)
	float crossHairY = 0.333333;

	UPROPERTY(EditDefaultsOnly)
	int32 lineTraceRange = 1000000;

private:
	bool getSightRayHitLocation(FVector &OUTHitLocation);

	bool getLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

	bool getLookDirection(FVector2D screenLocation, FVector& worldDirection) const;
	
	UFUNCTION()
	void OnTankDeath();
private:


	
};
