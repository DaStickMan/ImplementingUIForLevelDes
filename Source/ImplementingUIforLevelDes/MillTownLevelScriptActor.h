// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InitViewportCharacter.h"
#include "UserWidgetPlayerUI.h"
#include "InteractiveSwitchActor.h"
#include "ActorDoor.h"
#include "KeyParentActor.h"
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
	bool GearMachineInspected;

public:
	
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBridgeControllNoPower();

	UFUNCTION(BlueprintCallable)
	void OnBridgeExtended();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool KeyFound;

private:
	// Function to handle overlap events
	UFUNCTION()
	void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorBeginOverlap2(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorBeginOverlap3(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnActorBeginOverlap4(AActor* OverlappedActor, AActor* OtherActor);

	void HideNarrativeText();

	UFUNCTION()
	void OnGearMachineInspectedHandler();

	UFUNCTION()
	void OnGearMachineStartedHandler();

	UFUNCTION()
	void OnDoorInteractHandler();	
	
	UFUNCTION()
	void OnCrowbarTakenHandler();

	UFUNCTION()
	void OnKeyTakenHandler();

	UFUNCTION()
	void OnGearWheelHandler();

	UFUNCTION()
	void OnObjectiveMarkerReached(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// Reference to the TriggerBox in the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox; // Make sure you set this in the editor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	ATriggerBox* TriggerBox4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerBridge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerBridge2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerGearMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerTownHill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerTownHill2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerReturnToMill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerRetriveGear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectiveMarker", meta = (AllowPrivateAccess = "true"))
	AObjectiveMarker* ObjectiveMarkerFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GearMachine", meta = (AllowPrivateAccess = "true"))
	AInteractiveSwitchActor* GearMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	AActorDoor* DoorInteractive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	AActorDoor* DoorLoadingDock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowbar", meta = (AllowPrivateAccess = "true"))
	AKeyParentActor* CrowbarInteractive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key", meta = (AllowPrivateAccess = "true"))
	AKeyParentActor* KeyInteractive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key", meta = (AllowPrivateAccess = "true"))
	AKeyParentActor* GearWheelInteractive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key", meta = (AllowPrivateAccess = "true"))
	AInteractiveSwitchActor* InteractiveSwitchBridge;
};
