// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	driveTrack();
	applySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::applySidewaysForce()
{
	float slipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	float deltaTime = GetWorld()->GetDeltaSeconds();

	FVector correctionAcceleration = -slipSpeed / deltaTime * GetRightVector();

	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;

	tankRoot->AddForce(correctionForce);
}

void UTankTrack::setThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::driveTrack()
{
	//1) direction of force, 2) the force for movement, 3) modifier for how much of the max force we use(only for controllers).
	FVector forceApplied = GetForwardVector() * DrivingForce * currentThrottle;

	//track's origen
	FVector forceLocation = GetComponentLocation();

	//Cast<UPrimitiveComponent> so we can use tankRoot->AddForceAtLocation.
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//add force to track origen
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}





