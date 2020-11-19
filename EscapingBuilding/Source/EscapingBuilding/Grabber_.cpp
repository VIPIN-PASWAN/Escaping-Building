// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber_.h"

#define OUT       //BLANK MECRO

// Sets default values for this component's properties
UGrabber_::UGrabber_()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber_::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber_::FindPhysicsHandleComponent() {

	//looking for attachment of Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr)
		UE_LOG(LogTemp, Error, TEXT("%s physics handle missing"), *(GetOwner()->GetName()));
}

void UGrabber_::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("INPUTCOMPONENT Found "));
		///input action Grab 
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber_::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber_::Release);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("%s input components missing"), *(GetOwner()->GetName()));

	}
}


// Called every frame
void UGrabber_::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	if (PhysicsHandle->GrabbedComponent) {
		///move the object that is holded
		PhysicsHandle->SetTargetLocationAndRotation(LineTraceEnd, PlayerViewPointRotation);
	}
	

}

void UGrabber_::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed....."));

	///LINE TRACE & if phy. handle is attached
	auto HitResult = GetFirstPhysicsBodyInRech();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		///Try and reach any actor with physics body collision channnel
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
		//if it hit something the attach phy. handle
	}
}

void UGrabber_::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released....."));
	PhysicsHandle->ReleaseComponent();
}



const FHitResult UGrabber_::GetFirstPhysicsBodyInRech()
{
	//Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;


	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s ::LineTrace "), *(ActorHit->GetName()));
	}
	return Hit;
}