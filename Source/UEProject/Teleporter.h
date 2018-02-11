// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Teleporter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API UTeleporter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleporter();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	UInputComponent* InputComponent = nullptr;
	// Location of positioned teleport
	FVector TeleportLocation;
	const float MAX_TELEPORT_HEIGHT = 200.f;

	// Setup attached Input component
	void FindInputComponent();
	// Set the location to which teleport
	void PlaceTeleportLocation();
	// Teleport to the selected location
	void Teleport();
};
