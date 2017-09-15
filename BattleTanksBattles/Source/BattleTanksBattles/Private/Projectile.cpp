// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("projectile movement component"));

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("launch Blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("impact Blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	projectileMovementComponent->bAutoActivate = false;
	impactBlast->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//turns off the smoke trail, turns on the impact explosion and adds an impact force to the tank
	launchBlast->Deactivate();
	impactBlast->Activate(true);
	explosionForce->FireImpulse();

	//sets rootcomponent as impactblast to make it still happen once we destroy the collision mesh
	SetRootComponent(impactBlast);
	collisionMesh->DestroyComponent();

	
	UGameplayStatics::ApplyRadialDamage(this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius, //same as the impulse force
		UDamageType::StaticClass(),
		TArray<AActor*>() //damage all actors, ignore nothing
		);

	//despawns the projectiles after a set timer 
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::DestroyProjectile, DestroyDelay, false);


}


//make the projectile move forwards 
void AProjectile::launchProjectile(float speed)
{
	projectileMovementComponent->Activate(true);
	//moves the blueprint not just the staticmesh
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
}

void AProjectile::DestroyProjectile()
{
	//destroys everything
	Destroy();
}

