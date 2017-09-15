// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

//reletiveSpeed is between -1 and +1 min or max
void UTankBarrel::Elevate(float reletiveSpeed)
{
	float elevationChange = FMath::Clamp<float>(reletiveSpeed, -1.0f, 1.0f) * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationChange, minElevation, maxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0.0f, 0.0f));
}



