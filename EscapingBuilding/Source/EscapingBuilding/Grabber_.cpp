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

}


// Called every frame
void UGrabber_::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayereViewPointRotation;
	// ray-cast 

	//see what we hits

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayereViewPointRotation);

	//FString ObjectName = GetOwner()->GetName();
	//FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Location:%s Rotaion: %s"), *PlayerViewPointLocation.ToString(), *PlayereViewPointRotation.ToString());
}

