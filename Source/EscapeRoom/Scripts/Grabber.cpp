// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Components/PrimitiveComponent.h"
#include "Public/DrawDebugHelpers.h"

//Used to more easily tell when variables are used as out parameters
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	playerController = GetOwner();

	FindComponents();
	
	///Bind input axis
	BindInputs();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle->GrabbedComponent) {
		FVector playerReachEnd = GetPlayerReach();
		physicsHandle->SetTargetLocation(playerReachEnd);
	}
}


void UGrabber::FindComponents()
{
	physicsHandle = playerController->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = playerController->FindComponentByClass<UInputComponent>();
	//Check if components aren't found
	if (!physicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s"), *playerController->GetName());
	}
	if (!inputComponent) {
		UE_LOG(LogTemp, Error, TEXT("No input component found on %s"), *playerController->GetName());
	}
}

void UGrabber::BindInputs()
{
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	FHitResult hitResult = GetFirstPhysicsBodyInReach();

	if (hitResult.GetActor()) {
		UPrimitiveComponent* objectToGrab = hitResult.GetComponent();
		physicsHandle->GrabComponentAtLocationWithRotation(objectToGrab, NAME_None, objectToGrab->GetOwner()->GetActorLocation(), objectToGrab->GetOwner()->GetActorRotation());
	}
	
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	physicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	///Get a vector that determines the furthest point the player can reach
	FVector playerReachEnd = GetPlayerReach();

	///Setup query parameters
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
	///Raycast(AKA Line-trace) a set distance
	FHitResult lineTraceHit;
	bool traceHit = GetWorld()->LineTraceSingleByObjectType(lineTraceHit, playerController->GetActorLocation(), playerReachEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), queryParams);
	///See what raycast hits
	if (traceHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *lineTraceHit.GetActor()->GetName());
	}

	return lineTraceHit;
}

FVector UGrabber::GetPlayerReach() const
{
	FVector actorViewVector;
	FRotator actorViewRotation;
	playerController->GetActorEyesViewPoint(OUT actorViewVector, OUT actorViewRotation);

	///Return a vector that determines the furthest point the player can reach
	return actorViewVector + actorViewRotation.Vector() * reach;
}
