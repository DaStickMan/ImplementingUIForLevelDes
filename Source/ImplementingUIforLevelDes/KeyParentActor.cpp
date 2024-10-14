// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyParentActor.h"

// Sets default values
AKeyParentActor::AKeyParentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeyParentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyParentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyParentActor::CrowbarTaken()
{
	if (OnCrowbarTaken.IsBound())
	{
		OnCrowbarTaken.Broadcast();
	}
}


void AKeyParentActor::KeysTaken()
{
	if (OnKeysTaken.IsBound())
	{
		OnKeysTaken.Broadcast();
	}
}

void AKeyParentActor::GearWheelTaken()
{
	if (OnGearWheelTaken.IsBound())
	{
		OnGearWheelTaken.Broadcast();
	}
}


