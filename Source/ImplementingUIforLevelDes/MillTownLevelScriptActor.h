// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InitViewportCharacter.h"
#include "UserWidgetPlayerUI.h"
#include "ObjectiveMarker.h"
#include <Engine/TriggerBox.h>
#include "Engine/LevelScriptActor.h"
#include "MillTownLevelScriptActor.generated.h"


/**
 * 
 */
UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AMillTownLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	AInitViewportCharacter* PlayerCharacter;
	UUserWidgetPlayerUI* PlayerUI;
	void InitializeUI();
	void OBJ_FindAWayAcross();
	FTimerHandle MemberTimerHandle;

public:
	
	void BeginPlay() override;

private:
	// Function to handle overlap events
	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorBeginOverlap2(AActor* OverlappedActor, AActor* OtherActor);

	void HideNarrativeText();

	// Reference to the TriggerBox in the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox; // Make sure you set this in the editor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerBridge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerBridge2;
};
