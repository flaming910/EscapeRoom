// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Public/DrawDebugHelpers.h"


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
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///Get what player is looking at and print it to log
	FVector actorViewVector;
	FRotator actorViewRotation;
	playerController->GetActorEyesViewPoint(actorViewVector, actorViewRotation);
	FString vectorString = actorViewVector.ToString();
	FString rotationString = actorViewRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Player looking at: %s %s"), *vectorString, *rotationString);

	///Draw line to show player reach
	FVector actorDirectionVector = actorViewRotation.Vector() * reach;
	FVector viewEndPoint = actorViewVector + actorDirectionVector;	
	DrawDebugLine(GetWorld(), actorViewVector, viewEndPoint, FColor(0, 0, 255), false, 0.f, 0, 2.f);

	///Setup query parameters
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	///Raycast(AKA Line-trace) a set distance
	FHitResult lineTraceHit;

	bool traceHit = GetWorld()->LineTraceSingleByObjectType(lineTraceHit, actorViewVector, viewEndPoint, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), queryParams);
	///See what raycast hits
	if (traceHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *lineTraceHit.GetActor()->GetName());
	}
}

