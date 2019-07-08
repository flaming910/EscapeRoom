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
	if (!pressurePlate1) {
		UE_LOG(LogTemp, Error, TEXT("No pressure plate set on %s"), *doorActor->GetName());
	}
	if (!pressurePlate2) {
		UE_LOG(LogTemp, Error, TEXT("No pressure plate set on %s"), *doorActor->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetMassOnPlate(pressurePlate1) >= massNeeded1 && GetMassOnPlate(pressurePlate2) >= massNeeded2) {
		onOpenRequest.Broadcast();
	} 
	else {
		onCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetMassOnPlate(ATriggerVolume* pressurePlate)
{
	float totalMass = 0.f;
	if (!pressurePlate1) {
		return 0.0f;
	} else{
		//Find actors on pressure plate
		TArray<AActor*> actorsOnPlate;

		pressurePlate->GetOverlappingActors(OUT actorsOnPlate);

		//Iterate through actorsOnPlate and add their mass to totalMass
		for (AActor* actor : actorsOnPlate) {
			UE_LOG(LogTemp, Warning, TEXT("Actor on plate: %s, Weight of Actor: %f"), *actor->GetName(), Cast<UPrimitiveComponent>(actor->GetRootComponent())->GetMass());
			totalMass += Cast<UPrimitiveComponent>(actor->GetRootComponent())->GetMass();
		}
	}
	return totalMass;
}

