// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); //getting ownening actor

	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{
	

	FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f); //getting rotaion in float (pitch , yan, roll)

	Owner->SetActorRotation(NewRotation);           //setting rotation
}

void UOpenDoor::CloseDoor()
{
	

	FRotator NewRotation = FRotator(0.f, 180.0f, 0.f); //getting rotaion in float (pitch , yan, roll)

	Owner->SetActorRotation(NewRotation);           //setting rotation
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorOnPlate()>17.f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();

}

float UOpenDoor::GetTotalMassOfActorOnPlate() 
{
	float TotalMass = 0.f;

	//Find All Actor MASS
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//autamatically Itterating
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	    UE_LOG(LogTemp, Warning, TEXT("%s IS OVERLAPPINGACTOR "), (*Actor->GetName()));
	}
	return TotalMass;
}