// Na

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!ensure(leftTrackToSet && rightTrackToSet)) { return; }
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//no need to call super::RequestDirectMove() because we are going to replace it's functionalaty

	//the direction the tank is facing
	FVector forwardsDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	//the direction in which the tank wants to move to get to the player (set in the AI controller)
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	//ai using our movement method this function is being used by the ai only
	intendMoveForward(FVector::DotProduct(forwardsDirection, AIForwardIntention));
	intendRotateLeft(FVector::CrossProduct(forwardsDirection, AIForwardIntention).Z);
}

void UTankMovementComponent::intendMoveForward(float Throw)
{
	if (!ensure(leftTrack) || !ensure(rightTrack)) { return; }

	leftTrack->setThrottle(Throw);
	rightTrack->setThrottle(Throw);
}

void UTankMovementComponent::intendRotateLeft(float Throw)
{
	if (!ensure(leftTrack) || !ensure(rightTrack)) { return; }

	leftTrack->setThrottle(-Throw);
	rightTrack->setThrottle(Throw);
}


