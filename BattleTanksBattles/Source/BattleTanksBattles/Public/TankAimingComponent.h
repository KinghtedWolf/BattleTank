// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringStatus : uint8 
{
	reloading,
	locked,
	aiming,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKSBATTLES_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//aims at the location the aiming retecule is pointing at if it can hit it
	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialise(UTankBarrel* tankBarrelToSet, UTankTurret* tankTurretToSet);

	//spawns a projectile and uses projectile class code to make it move
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void fire();

	EFiringStatus getFiringStatus() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringStatus = EFiringStatus::reloading;//must be reloading because we cant fire in the begining

private:
	//moves barrel up/down and rotates turret using code form their respective classes
	void moveBarrelTurret(FVector aimDirection);

	//check if (barrel or turret doesnt matter) is moving to set FiringStatus to aiming.
	bool isBarrelMoving();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetRoundsLeft() const;
private:
	//used in fire() to make projectile spawn at a socket location on the tank barrel static mesh
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector aimDirection;

	/**EditDefaultsOnly is so that you can only change the values in the blueprint causing all blueprints of the same type in the world
	*to have the same value.
	*How fast the projectile goes.*/
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float launchSpead = 170000.0f; //actual tank shell speed NEVER use this speed it's just for lolz 

	//used to tell unreal what exactly to spawn set in tank BP
	UPROPERTY(EditDefaultsOnly, Category = "Firing Projectile")
	TSubclassOf<AProjectile> projectileBP;

	//the time it takes between each tank shell to fire used in fire()
	UPROPERTY(EditDefaultsOnly, Category = "Firing Projectile")
	float reloadTime = 2.5f;

	float timeFired = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing Projectile")
	int32 roundsLeft = 3;
};
