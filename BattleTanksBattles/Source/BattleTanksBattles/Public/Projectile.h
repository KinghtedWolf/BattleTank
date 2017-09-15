// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKSBATTLES_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//make the projectile move forwards 
	void launchProjectile(float speed);	

private:
	//UFUNCTION() needed for OnHit to work.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyProjectile();

private:
	//so that we can properly set when the tank shell should be fired
	UProjectileMovementComponent* projectileMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "particleSystemSetup")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "particleSystemSetup")
	UParticleSystemComponent*  launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "particleSystemSetup")
	UParticleSystemComponent*  impactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "particleSystemSetup")
	URadialForceComponent*  explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Destroy Delay")
	float DestroyDelay = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Damage")
	float projectileDamage = 10.0f;

};
