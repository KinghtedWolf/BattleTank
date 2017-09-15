// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	//makes ui appere only when the aiming component is set
	foundAimingComponent(aimingComponent);

	

}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	aimToCrossHair();
}


void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (!ensure(GetPawn())) { return; }//might not been possesed
	ATank* playerTank = Cast<ATank>(GetPawn());

	playerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}


void  ATankPlayerController::aimToCrossHair()
{
	FVector hitLocation;

	if (!ensure(GetPawn())) { return; }

	//aiming component set here
	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	if (getSightRayHitLocation(hitLocation))
	{
		aimingComponent->aimAt(hitLocation);
	}
}


//for line tracing through a point on a screen
bool ATankPlayerController::getSightRayHitLocation(FVector &OUTHitLocation)
{
	FVector lookDirection;
	int32 veiwPortSizeX, veiwPortSizeY;

	GetViewportSize(veiwPortSizeX, veiwPortSizeY);
	FVector2D crossHairLocation = FVector2D(veiwPortSizeX * crossHairX, veiwPortSizeY * crossHairY);

	if (getLookDirection(crossHairLocation, lookDirection))
	{
		return getLookVectorHitLocation(lookDirection, OUTHitLocation);
	}
	
	//if it cant get a hitlocation return false
	return false;
}

bool ATankPlayerController::getLookDirection(FVector2D crossHairLocation, FVector& worldDirection) const
{
	FVector cameraLocation;//ussless
	return DeprojectScreenPositionToWorld(crossHairLocation.X, crossHairLocation.Y, cameraLocation, worldDirection);
}



bool ATankPlayerController::getLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FHitResult hit;
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = cameraLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		hit,
		cameraLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		hitLocation = hit.Location;
		return true;
	}
	hitLocation = FVector(0.0f, 0.0f, 0.0f);
	return false;
}



