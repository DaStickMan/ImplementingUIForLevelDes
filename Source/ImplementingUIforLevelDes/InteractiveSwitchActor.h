// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include "GameFramework/Actor.h"
#include "InteractiveSwitchActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGearMachineInspected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGearMachineStarted);

UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AInteractiveSwitchActor : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AInteractiveSwitchActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate that gets called when the gear machine is inspected
	UPROPERTY(BlueprintAssignable, Category = "GearMachine")
	FOnGearMachineInspected OnGearMachineInspected;

	// Function to be called when the event occurs
	UFUNCTION(BlueprintCallable)
	void InspectGearMachine();

	// Delegate that gets called when the gear machine is inspected
	UPROPERTY(BlueprintAssignable, Category = "GearMachine")
	FOnGearMachineStarted OnGearMachineStarted;

	// Function to be called when the event occurs
	UFUNCTION(BlueprintCallable)
	void GearMachineStarted();

	void EnableInteraction(bool enable);

	void CallUnlock();

private:
	UPROPERTY(EditAnywhere, Category = "Collisions")
	UShapeComponent* InteractRad;

	UPROPERTY(EditAnywhere, Category = "Collisions")
	UBoxComponent* InteractCol;

	UPROPERTY(EditAnywhere, Category = "Collisions")
	bool EnableInteractive;
};
