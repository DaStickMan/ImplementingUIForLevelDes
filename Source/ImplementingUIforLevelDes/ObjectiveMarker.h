// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Components/BillboardComponent.h"
#include "ObjectiveMarker.generated.h"

UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AObjectiveMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* ObjectiveMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBillboardComponent* BillboardMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TriggerSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DisabledOnReach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AObjectiveMarker* NextObjectMarker;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
