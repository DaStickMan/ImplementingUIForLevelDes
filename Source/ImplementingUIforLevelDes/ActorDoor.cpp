// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorDoor.h"

// Sets default values
AActorDoor::AActorDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorDoor::InteractLoked()
{
	if (OnDoorInteractLocked.IsBound())
	{
		OnDoorInteractLocked.Broadcast();
	}
}

void AActorDoor::CallUnlockDoor()
{
    // Check if the function exists in the Blueprint
    FName EventName = "UnlockDoor";  // The name must match the Blueprint event's name
    UFunction* BlueprintEvent = FindFunction(EventName);

    // If the function is found, we can call it
    if (BlueprintEvent)
    {
        ProcessEvent(BlueprintEvent, nullptr);  // Pass null for parameters if there are no inputs
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Blueprint event 'UnlockDoor' not found!"));
    }
}

void AActorDoor::CallOpenDoorExternal()
{
    bool Enable = true;
    // Check if the function exists in the Blueprint
    FName EventName = "OpenDoorExternal";  // The name must match the Blueprint event's name
    UFunction* BlueprintEvent = FindFunction(EventName);

    // If the function is found, we can call it
    if (BlueprintEvent)
    {
        ProcessEvent(BlueprintEvent, &Enable);  // Pass null for parameters if there are no inputs
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Blueprint event 'OpenDoorExternal' not found!"));
    }
}

