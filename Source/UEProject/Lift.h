// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Lift.generated.h"

UENUM(BlueprintType)
enum class ESequence : uint8 {
	XYZ,
	XZY,
	YXZ,
	YZX,
	ZXY,
	ZYX
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API ULift : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULift();

	void MoveUp();
	void MoveDown();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	AActor* Owner;
	AActor* ActorThatMoves; //Pawn inherits from actor

	FVector InitialLocation = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere)
	FVector FinalLocation = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere)
	ESequence Sequence = ESequence::XYZ;

	///if true the pressure plate moves with the Actor
	UPROPERTY(EditAnywhere)
	bool MovePressurePlate = false;

	///decide if moves from initial position to final or from final to initial
	bool fromInitialToFinal = true;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
	float MassToTriggerPressurePlate = 50.f;

	UPROPERTY(EditAnywhere)
	float StartDelay = 0.f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.f;

	/// Returns total mass
	float ULift::GetTotalMassOfActorsOnPlate();

	/// Decides the sequence the presure plate moves
	void ULift::MovePressurePlateToFinalPosition();
	void ULift::MovePressurePlateToInitialPosition();

	void ULift::MoveOnX(FVector, FVector);

	void ULift::MoveOnY(FVector, FVector);

	void ULift::MoveOnZ(FVector, FVector);
};
