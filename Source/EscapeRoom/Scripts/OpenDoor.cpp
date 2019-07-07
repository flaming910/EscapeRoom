// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Engine/World.h"

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
	doorActor = GetOwner();
	//ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	doorActor->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	doorActor->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOnPlate() >= massNeeded) {
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	} 
	else if(lastDoorOpenTime + doorCloseDelay <= GetWorld()->GetTimeSeconds()){
		CloseDoor();
	}
}

float UOpenDoor::GetMassOnPlate()
{
	float totalMass = 0.f;

	//Find actors on pressure plate
	TArray<AActor*> actorsOnPlate;

	pressurePlate->GetOverlappingActors(OUT actorsOnPlate);

	//Iterate through actorsOnPlate and add their mass to totalMass
	for (AActor* actor : actorsOnPlate) {
		UE_LOG(LogTemp, Warning, TEXT("Actor on plate: %s, Weight of Actor: %f"), *actor->GetName(), Cast<UPrimitiveComponent>(actor->GetRootComponent())->GetMass());
		totalMass += Cast<UPrimitiveComponent>(actor->GetRootComponent())->GetMass();
	}
	return totalMass;
}

