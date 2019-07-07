// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest onOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest onCloseRequest;

private:

	UPROPERTY(EditAnywhere)
	float openAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float massNeeded;

	//UPROPERTY(BlueprintAssignable)
	

	float lastDoorOpenTime;
	AActor* doorActor = nullptr;

	float GetMassOnPlate();

};
