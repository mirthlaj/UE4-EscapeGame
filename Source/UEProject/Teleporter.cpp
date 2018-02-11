// Fill out your copyright notice in the Description page of Project Settings.

#include "UEProject.h"
#include "Teleporter.h"
#include "Grabber.h"

// Sets default values for this component's properties
UTeleporter::UTeleporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleporter::BeginPlay()
{
	Super::BeginPlay();

	FindInputComponent();
}

void UTeleporter::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		// Bind the input action
		InputComponent->BindAction("PlaceTeleportLocation", IE_Pressed, this, &UTeleporter::PlaceTeleportLocation);
		InputComponent->BindAction("Teleport", IE_Pressed, this, &UTeleporter::Teleport);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UTeleporter::PlaceTeleportLocation() {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation
	);
	if (PlayerViewPointLocation.Z < MAX_TELEPORT_HEIGHT) {
		TeleportLocation = PlayerViewPointLocation;
	}
}

void UTeleporter::Teleport() {
	GetWorld()->GetFirstPlayerController()->GetCharacter()->SetActorLocation(TeleportLocation, false);
}

// Called every frame
void UTeleporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

