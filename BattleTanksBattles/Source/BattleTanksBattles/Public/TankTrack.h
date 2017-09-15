// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Class used to set forces to the tank used for driving.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKSBATTLES_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void applySidewaysForce();

	void BeginPlay();

	//Digital ammount of throttle
	UFUNCTION(BlueprintCallable, Category = "trackSetup")
	void setThrottle(float throttle);

	void driveTrack();


public:
	//max driving force on the tracks in Newtons. Deafault of m1 abrahams
	UPROPERTY(EditDefaultsOnly, Category = "trackSetup")
	float DrivingForce = 766200;

private:
	//UFUNCTION() needed for OnHit to work.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	float currentThrottle = 0;

};
