// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	timeFired = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT(""))

	//aiming retecule code
	if (roundsLeft == 0) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - timeFired) < reloadTime)
	{
		FiringStatus = EFiringStatus::reloading;
	}
	else if (isBarrelMoving())
	{
		FiringStatus = EFiringStatus::aiming;
	}
	else {
		FiringStatus = EFiringStatus::locked;
	}
}

//aims at the location the aiming retecule is pointing at if it can hit it with the given projectile speed
void UTankAimingComponent::aimAt(FVector hitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OUTlaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUTlaunchVelocity,
		startLocation,
		hitLocation,
		launchSpead,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	/*, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true*/);

	if (bHaveAimSolution)
	{
		//unit vector
		aimDirection = OUTlaunchVelocity.GetSafeNormal();
		moveBarrelTurret(aimDirection);
	}
}

//sets a barrel/turret bp to the barrel/turret class in blueprint
void UTankAimingComponent::initialise(UTankBarrel * tankBarrelToSet, UTankTurret * tankTurretToSet)
{
	if (!ensure(tankBarrelToSet) || !ensure(tankTurretToSet)) { return; }
	Barrel = tankBarrelToSet;
	Turret = tankTurretToSet;
}

//moves barrel up/down and rotates turret using code form their respective classes
void UTankAimingComponent::moveBarrelTurret(FVector aimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	FRotator barrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotation = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotation - barrelRotation;

	Barrel->Elevate(deltaRotator.Pitch);
	//makes turret go the right way round
	if (FMath::Abs(deltaRotator.Yaw) >= 180)
	{
		Turret->yaw(-deltaRotator.Yaw);
	}
	else {
		Turret->yaw(deltaRotator.Yaw);
	}

}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector barrelForwards = Barrel->GetForwardVector();

	return !(barrelForwards.Equals(aimDirection, 0.01));
}


//spawns a projectile and uses projectile class code to make it move
//uses timeFired, reloadTime, barrel, projectileBP, launchSpead
void UTankAimingComponent::fire()
{
	if (!ensure(Barrel) || !ensure(projectileBP)) { return; }

	//won't fire if the retecule is red or no ammo is left
	if (FiringStatus != EFiringStatus::reloading && roundsLeft > 0)
	{
		//put projectile in the world 
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		//launchProjectile in projectile.cpp/h
		//launches projectile at a speed only when called
		if (!ensure(projectile)) { return; }
		projectile->launchProjectile(launchSpead);
		//decrese each time it fires
		roundsLeft--;

		timeFired = GetWorld()->GetTimeSeconds();
	}
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return roundsLeft;
}

EFiringStatus UTankAimingComponent::getFiringStatus() const
{
	return FiringStatus;
}
