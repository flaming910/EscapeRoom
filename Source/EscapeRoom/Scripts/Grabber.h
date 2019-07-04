// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Classes/Engine/World.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	AActor* playerController = nullptr;
	float reach = 100.f;
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;
	//Find Components
	void FindComponents();
	//Bind Inputs
	void BindInputs();
	//Line trace player reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Grab in-reach objects
	void Grab();
	//Release grabbed objects
	void Release();

	
};
