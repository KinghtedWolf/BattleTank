// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::yaw(float reletiveSpeed)
{
	//clamping speed
	float yawChange = FMath::Clamp<float>(reletiveSpeed, -1.0f, 1.0f) * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Newyaw = RelativeRotation.Yaw + yawChange;

	SetRelativeRotation(FRotator(0.0f, Newyaw, 0.0f));
}


