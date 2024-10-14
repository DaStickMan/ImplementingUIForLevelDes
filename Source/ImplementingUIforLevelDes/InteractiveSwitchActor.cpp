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
void AInteractiveSwitchActor::Unlock_Implementation()
{
	if (this->GetClass()->ImplementsInterface(UBPI_Interaction::StaticClass()))
	{
		IBPI_Interaction::Execute_Unlock(this);
	}
}