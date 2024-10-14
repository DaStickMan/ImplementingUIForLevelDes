// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPI_Interaction.h" 
#include "GameFramework/Actor.h"
#include "ActorDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorInteractLocked);

UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AActorDoor : public AActor, public IBPI_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "DoorInteract")
	FOnDoorInteractLocked OnDoorInteractLocked;

	UFUNCTION(BlueprintCallable, Category = "DoorInteract")
	void InteractLoked();

	void CallUnlockDoor();

	void CallOpenDoorExternal();

	// This overrides the function from the interface
	virtual void Unlock_Implementation() override;
};
