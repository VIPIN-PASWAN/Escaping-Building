// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber_.h"

#define OUT       //BLANK MECRO


// Sets default values for this component's properties
UGrabber_::UGrabber_()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UGrabber_::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber on duty!"));

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{}

	else {
		UE_LOG(LogTemp, Error, TEXT("%s physics handle missing"), *(GetOwner()->GetName()));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("INPUTCOMPONENT Found "));

		///input action Grab 
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber_::Grab);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("%s input components missing"), *(GetOwner()->GetName()));



	}
}
 
void UGrabber_::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed....."));
}



// Called every frame
void UGrabber_::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	// UE_LOG(LogTemp, Warning, TEXT("Location:%s Rotaion: %s"), *PlayerViewPointLocation.ToString(), *PlayereViewPointRotation.ToString());

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	FHitResult Hit;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ::LineTrace "), *(ActorHit->GetName()));
	}
}