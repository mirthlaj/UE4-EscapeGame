// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float Reach = 200.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	bool IsHoldingCube = false;

	// Find attached Physics Handle
	void FindPhysicsHandleComponent();
	// Setup attached Input component
	void FindInputComponent();
	// Ray-cast and grab what is in reach or release
	void GrabOrRelease();
	void Grab();
	void Release();
	// Retrun start of reach line
	FVector GetReachLineStart();
	// Retrun end of reach line
	FVector GetReachLineEnd();
	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach();
};
