// Fill out your copyright notice in the Description page of Project Settings.

#include "UEProject.h"
#include "Lift.h"


// Sets default values for this component's properties
ULift::ULift()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULift::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	InitialLocation = Owner->GetActorLocation();

	ActorThatMoves = GetWorld()->GetFirstPlayerController()->GetCharacter();

	if (MoveSpeed > 5.f) {
		MoveSpeed = 5.f;
	}

	InitialLocation.X = floor(InitialLocation.X);
	InitialLocation.Y = floor(InitialLocation.Y);
	InitialLocation.Z = floor(InitialLocation.Z);
	FinalLocation.X = ceil(FinalLocation.X);
	FinalLocation.Y = ceil(FinalLocation.Y);
	FinalLocation.Z = ceil(FinalLocation.Z);
	FinalLocation.X -= fmod(FinalLocation.X - InitialLocation.X, MoveSpeed);
	FinalLocation.Y -= fmod(FinalLocation.Y - InitialLocation.Y, MoveSpeed);
	FinalLocation.Z -= fmod(FinalLocation.Z - InitialLocation.Z, MoveSpeed);
}

//void ULift::MoveUp()
//{
//	FVector CurrentLocation = Owner->GetActorLocation();
//	FVector PressurePlateLocation = PressurePlate->GetActorLocation();
//	if (CurrentLocation.Z < maxZ) {
//		Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, 1.f));
//		PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, 1.f));
//	}
//	else {
//		UpMove = false;
//	}
//}
//
//void ULift::MoveDown()
//{
//	FVector CurrentLocation = Owner->GetActorLocation();
//	FVector PressurePlateLocation = PressurePlate->GetActorLocation();
//	if (CurrentLocation.Z > minZ) {
//		Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, -1.f));
//		PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, -1.f));
//	}
//	else {
//		UpMove = true;
//	}
//}

// Called every frame
void ULift::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (GetTotalMassOfActorsOnPlate() >= MassToTriggerPressurePlate)
	{
		StartDelay -= DeltaTime;
		if (StartDelay < 0) {
			StartDelay = 0.f;
			if (fromInitialToFinal) {
				ULift::MovePressurePlateToFinalPosition();
			}
			else {
				ULift::MovePressurePlateToInitialPosition();
			}
		}
		
	}
	
}

float ULift::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlapingActors;

	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlapingActors);

	for (const AActor* Actor : OverlapingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

#pragma region MovePressurePlateToFinalPosition
void ULift::MovePressurePlateToFinalPosition()
{
	FVector CurrentLocation = Owner->GetActorLocation();
	FVector PressurePlateLocation = PressurePlate->GetActorLocation();
	switch (Sequence)
	{
	case ESequence::XYZ:
#pragma region XYZ
		if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::XZY:
#pragma region XZY
		if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::YXZ:
#pragma region YXZ
		if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::YZX:
#pragma region YZX
		if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::ZXY:
#pragma region ZXY
		if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::ZYX:
#pragma region ZYX
		if (CurrentLocation.Z != FinalLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != FinalLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != FinalLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region MovePressurePlateToInitialPosition
void ULift::MovePressurePlateToInitialPosition()
{
	FVector CurrentLocation = Owner->GetActorLocation();
	FVector PressurePlateLocation = PressurePlate->GetActorLocation();
	switch (Sequence)
	{
	case ESequence::XYZ:
#pragma region XYZ
		if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::XZY:
#pragma region XZY
		if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::YXZ:
#pragma region YXZ
		if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::YZX:
#pragma region YZX
		if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::ZXY:
#pragma region ZXY
		if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	case ESequence::ZYX:
#pragma region ZYX
		if (CurrentLocation.X != InitialLocation.X) {
			ULift::MoveOnX(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Y != InitialLocation.Y) {
			ULift::MoveOnY(CurrentLocation, PressurePlateLocation);
		}
		else if (CurrentLocation.Z != InitialLocation.Z) {
			ULift::MoveOnZ(CurrentLocation, PressurePlateLocation);
		}
		else {
			fromInitialToFinal = !fromInitialToFinal;
		}
#pragma endregion
		break;
	default:
		break;
	}
}

#pragma endregion



void ULift::MoveOnX(FVector CurrentLocation, FVector PressurePlateLocation)
{
	if (fromInitialToFinal) {
		if (CurrentLocation.X < FinalLocation.X) {
			Owner->SetActorLocation(CurrentLocation + FVector(MoveSpeed, 0.f, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(MoveSpeed, 0.f, 0.f));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(-MoveSpeed, 0.f, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(-MoveSpeed, 0.f, 0.f));
			}
		}
	}
	else {
		if (CurrentLocation.X < InitialLocation.X) {
			Owner->SetActorLocation(CurrentLocation + FVector(MoveSpeed, 0.f, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(MoveSpeed, 0.f, 0.f));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(-MoveSpeed, 0.f, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(-MoveSpeed, 0.f, 0.f));
			}
		}
	}
}

void ULift::MoveOnY(FVector CurrentLocation, FVector PressurePlateLocation)
{
	if (fromInitialToFinal) {
		if (CurrentLocation.Y < FinalLocation.Y) {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, MoveSpeed, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, MoveSpeed, 0.f));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, -MoveSpeed, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, -MoveSpeed, 0.f));
			}
		}
	}
	else {
		if (CurrentLocation.Y < InitialLocation.Y) {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, MoveSpeed, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, MoveSpeed, 0.f));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, -MoveSpeed, 0.f));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, -MoveSpeed, 0.f));
			}
		}
	}
}

void ULift::MoveOnZ(FVector CurrentLocation, FVector PressurePlateLocation)
{
	if (fromInitialToFinal) {
		if (CurrentLocation.Z < FinalLocation.Z) {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, MoveSpeed));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, MoveSpeed));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, -MoveSpeed));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, -MoveSpeed));
			}
		}
	}
	else {
		if (CurrentLocation.Z < InitialLocation.Z) {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, MoveSpeed));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, MoveSpeed));
			}
		}
		else {
			Owner->SetActorLocation(CurrentLocation + FVector(0.f, 0.f, -MoveSpeed));
			if (MovePressurePlate) {
				PressurePlate->SetActorLocation(PressurePlateLocation + FVector(0.f, 0.f, -MoveSpeed));
			}
		}
	}
}