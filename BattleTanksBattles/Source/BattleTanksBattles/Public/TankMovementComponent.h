// Na

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKSBATTLES_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:
	//Throw is the throttle throw ammount
	UFUNCTION(BlueprintCallable)
	void intendMoveForward(float Throw);

	//by how much the tank wants to rotate by
	UFUNCTION(BlueprintCallable)
	void intendRotateLeft(float Throw);

	//sets a few thing before all other code can run
	UFUNCTION(BlueprintCallable)
	void initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	//if the tank wants to move we must move it 
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:

	UTankTrack* leftTrack = nullptr;

	UTankTrack* rightTrack = nullptr;
	
};
