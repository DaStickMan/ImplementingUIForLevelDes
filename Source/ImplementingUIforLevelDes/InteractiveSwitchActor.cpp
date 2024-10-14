// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveSwitchActor.h"

// Sets default values
AInteractiveSwitchActor::AInteractiveSwitchActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveSwitchActor::BeginPlay()
{
	Super::BeginPlay();

	InteractCol = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("InteractCollision")));
	InteractRad = Cast<UShapeComponent>(GetDefaultSubobjectByName(TEXT("InteractRadius")));

	EnableInteraction(EnableInteractive);
}

// Called every frame
void AInteractiveSwitchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveSwitchActor::InspectGearMachine()
{
	if (OnGearMachineInspected.IsBound())
	{
		OnGearMachineInspected.Broadcast();
	}
}

void AInteractiveSwitchActor::GearMachineStarted()
{
	if (OnGearMachineStarted.IsBound())
	{
		OnGearMachineStarted.Broadcast();
	}
}

void AInteractiveSwitchActor::EnableInteraction(bool enable)
{
	if (InteractCol && InteractRad)
	{
		if (enable)
		{
			InteractCol->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			InteractRad->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			InteractCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InteractRad->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void AInteractiveSwitchActor::CallUnlock()
{
	// Check if the function exists in the Blueprint
	FName EventName = "Unlock";  // The name must match the Blueprint event's name
	UFunction* BlueprintEvent = FindFunction(EventName);

	// If the function is found, we can call it
	if (BlueprintEvent)
	{
		ProcessEvent(BlueprintEvent, nullptr);  // Pass null for parameters if there are no inputs
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Blueprint event 'Unlock' not found!"));
	}
}

