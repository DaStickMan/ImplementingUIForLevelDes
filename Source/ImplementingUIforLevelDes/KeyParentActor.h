// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyParentActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCrowbarTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKeysTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGearWheelTaken);


UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AKeyParentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyParentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "CrowbarTaken")
	FOnCrowbarTaken OnCrowbarTaken;

	UFUNCTION(BlueprintCallable, Category = "CrowbarTaken")
	void CrowbarTaken();

	UPROPERTY(BlueprintAssignable, Category = "OnKeysTaken")
	FOnKeysTaken OnKeysTaken;

	UFUNCTION(BlueprintCallable, Category = "OnKeysTaken")
	void KeysTaken();

	UPROPERTY(BlueprintAssignable, Category = "OnGearWheelTaken")
	FOnGearWheelTaken OnGearWheelTaken;

	UFUNCTION(BlueprintCallable, Category = "OnGearWheelTaken")
	void GearWheelTaken();
};
