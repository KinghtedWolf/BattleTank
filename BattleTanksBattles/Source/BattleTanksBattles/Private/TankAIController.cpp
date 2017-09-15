// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* controlledTank = GetPawn();
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();


	//ai uses nav mesh to move to players tank with a given radius 
	//ai tank will be constrained to use our tanks physics.

	if (ensure(playerPawn) && ensure(controlledTank) && ensure(aimingComponent))
	{
		MoveToActor(playerPawn, stopRadius);

		aimingComponent->aimAt(playerPawn->GetActorLocation());

		//only shoot if you have locked on to the tank
		if (aimingComponent->getFiringStatus() == EFiringStatus::locked)
		{
			aimingComponent->fire();
		}
	}
}

//only does stuff when pawn has been set
void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) 
	{
		possesedTank = Cast<ATank>(InPawn);
		if (!ensure(possesedTank)) { return; }
		possesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	possesedTank->DetachFromControllerPendingDestroy();
}

