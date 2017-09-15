// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank Body"));
	SetRootComponent(TankBody);
	
	blowUpFire = CreateDefaultSubobject<UParticleSystemComponent>(FName("blow Up Fire"));
	blowUpFire->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	blowUpFire->bAutoActivate = false;
	blowUpFire->SetVisibility(false);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = startingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) 
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp<int32>(damagePoints, 0, currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0) 
	{
		OnDeath.Broadcast();
		blowUpFire->Activate(true);
	}

	return damageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)currentHealth / (float)startingHealth;
}


