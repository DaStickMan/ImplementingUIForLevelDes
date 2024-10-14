// Fill out your copyright notice in the Description page of Project Settings.


#include "MillTownLevelScriptActor.h"
#include <Kismet/GameplayStatics.h>

void AMillTownLevelScriptActor::InitializeUI()
{
	PlayerCharacter = Cast<AInitViewportCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerUI = PlayerCharacter->InitViewportAndReturn();
	GearMachineInspected = false;
	//Calls a new objective after 3s
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::OBJ_FindAWayAcross, 3.0f, false);	
}

void AMillTownLevelScriptActor::OBJ_FindAWayAcross()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);

	if (PlayerUI)
	{
		PlayerUI->SetNewObjective(TEXT("Find a way across the river"), 1);
	}
}

void AMillTownLevelScriptActor::BeginPlay()
{
	InitializeUI();
	if (TriggerBox && TriggerBox2 && TriggerBox3 && TriggerBox4)
	{
		// Bind the overlap event
		TriggerBox->OnActorBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnActorBeginOverlap);
		TriggerBox2->OnActorBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnActorBeginOverlap2);
		TriggerBox3->OnActorBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnActorBeginOverlap3);
		TriggerBox4->OnActorBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnActorBeginOverlap4);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The TriggerBoxes are not set in the editor!"));
	}

	if (GearMachine)
	{
		if (!GearMachine->IsPendingKill()) // Check if the object is valid
		{
			UE_LOG(LogTemp, Warning, TEXT("Binding Gear Machine"));
			GearMachine->OnGearMachineInspected.AddDynamic(this, &AMillTownLevelScriptActor::OnGearMachineInspectedHandler);
			GearMachine->OnGearMachineStarted.AddDynamic(this, &AMillTownLevelScriptActor::OnGearMachineStartedHandler);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Object is pending kill, cannot bind delegate!"));
		}		
	}

	if (DoorInteractive)
	{
		DoorInteractive->OnDoorInteractLocked.AddDynamic(this, &AMillTownLevelScriptActor::OnDoorInteractHandler);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The DoorInteractive are not set in the editor!"));
	}

	if (CrowbarInteractive)
	{
		CrowbarInteractive->OnCrowbarTaken.AddDynamic(this, &AMillTownLevelScriptActor::OnCrowbarTakenHandler);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The CrowbarInteractive are not set in the editor!"));
	}

	if (KeyInteractive)
	{
		KeyInteractive->OnKeysTaken.AddDynamic(this, &AMillTownLevelScriptActor::OnKeyTakenHandler);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The KeyInteractive are not set in the editor!"));
	}

	if (GearWheelInteractive)
	{
		GearWheelInteractive->OnGearWheelTaken.AddDynamic(this, &AMillTownLevelScriptActor::OnGearWheelHandler);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("The GearWheelInteractive are not set in the editor!"));

	}
}

void AMillTownLevelScriptActor::OnBridgeControllNoPower()
{
	if (PlayerUI && ObjectiveMarkerGearMachine)
	{
		PlayerUI->ToggleObjective(1, true, true);
		ObjectiveMarkerBridge2->Enabled = false;

		//delay 2s

		PlayerUI->ShowNarrative(true, "The Bridge Controls have no power. The Mill's water wheel can provide power, but I'll need to restart the Mill Machinery.", 8);

		//delay 5s

		PlayerUI->SetNewObjective("Restart the Mill machinary", 1);
		PlayerUI->ToggleObjective(1, false, true);
		ObjectiveMarkerGearMachine->Enabled = true;
		GearMachine->EnableInteraction(true);
	}
}

void AMillTownLevelScriptActor::OnBridgeExtended()
{
	ObjectiveMarkerBridge2->Enabled = false;
	PlayerUI->CompleteObjective(1);
	//delay 3s
	PlayerUI->ToggleObjective(1, true, true);
	//dealy 2s
	PlayerUI->SetNewObjective("Cross the bridge", 1);
	PlayerUI->ToggleObjective(1, false, false);
	ObjectiveMarkerFinish->Enabled = true;
}

void AMillTownLevelScriptActor::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (PlayerUI && ObjectiveMarkerBridge)
	{
		FTimerHandle TimerHandle;

		TriggerBox->OnActorBeginOverlap.Clear();

		PlayerUI->ShowNarrative(true, "The bridge across the river is retracted. Perhaps if I can reach it I can find a way to extend the bridge.", 8);
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);
		
		PlayerUI->CompleteObjective(1);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->ToggleObjective(1, true, true);
			}, 2, false);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->SetNewObjective("Reach the bridge", 1);
				PlayerUI->ToggleObjective(1, false, false);

				ObjectiveMarkerBridge->Enabled = true;
			}, 3, false);
	}
}

void AMillTownLevelScriptActor::OnActorBeginOverlap2(AActor* OverlappedActor, AActor* OtherActor)
{
	if (PlayerUI && ObjectiveMarkerBridge2)
	{
		FTimerHandle TimerHandle;

		TriggerBox2->OnActorBeginOverlap.Clear();

		ObjectiveMarkerBridge->Enabled = false;

		PlayerUI->ShowNarrative(true, "The bridge across the river is retracted. Perhaps if I can reach it I can find a way to extend the bridge.", 8);
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);

		PlayerUI->CompleteObjective(1);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->ToggleObjective(1, true, true);
			}, 2, false);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->SetNewObjective("Extend the bridge", 1);
				PlayerUI->ToggleObjective(1, false, false);

				ObjectiveMarkerBridge2->Enabled = true;
			}, 3, false);
	}
}

void AMillTownLevelScriptActor::OnActorBeginOverlap3(AActor* OverlappedActor, AActor* OtherActor)
{
	if (PlayerUI)
	{
		PlayerUI->ToggleObjective(1, true, true);

		//delay 2s

		PlayerUI->SetNewObjective("Find a way inside the TOWN HALL", 1);
		PlayerUI->ToggleObjective(1, false, false);
	}
}

void AMillTownLevelScriptActor::OnActorBeginOverlap4(AActor* OverlappedActor, AActor* OtherActor)
{
	if (PlayerUI && ObjectiveMarkerTownHill2)
	{

		PlayerUI->CompleteObjective(1);
		ObjectiveMarkerTownHill2->Enabled = false;

		//delay 3s

		PlayerUI->ToggleObjective(1, true, true);
		PlayerUI->SetNewObjective("Search the TOWN HALL", 1);
		PlayerUI->ToggleObjective(1, false, false);
	}
}

void AMillTownLevelScriptActor::HideNarrativeText()
{
	if (PlayerUI)
	{
		PlayerUI->HideNarrative();
		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}
}

void AMillTownLevelScriptActor::OnGearMachineInspectedHandler()
{
	ObjectiveMarkerGearMachine->Enabled = false;
		
	PlayerUI->ShowNarrative(true, "The drive shaft of this machine produces power for the entire mill, but the GEAR WHEEL is missing.", 8);
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);
	PlayerUI->ToggleObjective(1, true, true);
	PlayerUI->SetNewObjective("Find the GEAR WHEEL", 1);
	GearMachineInspected = true;
}

void AMillTownLevelScriptActor::OnGearMachineStartedHandler()
{
	ObjectiveMarkerGearMachine->Enabled = false;
	PlayerUI->CompleteObjective(1);
	//delay 3s
	PlayerUI->ToggleObjective(1, true, true);
	//delay 2s
	PlayerUI->SetNewObjective("Extend the bridge", 1);
	PlayerUI->ToggleObjective(1, false, false);
	ObjectiveMarkerBridge2->Enabled = true;
	if (InteractiveSwitchBridge)
	{
		InteractiveSwitchBridge->Unlock_Implementation();
	}
}


void AMillTownLevelScriptActor::OnDoorInteractHandler()
{
	PlayerUI->CompleteObjective(1);
	PlayerUI->ToggleObjective(1, true, true);
	PlayerUI->SetNewObjective("Reach the TOWN HALL", 1);
	PlayerUI->ShowNarrative(true, "The Foreman locked the GEAR WHEEL here in this workshop long ago. If he went to the Town Hall, maybe I can find his key there.", 8);
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);
	ObjectiveMarkerTownHill->Enabled = true;
	ObjectiveMarkerTownHill->DisabledOnReach = true;
	DoorLoadingDock->CallUnlockDoor();
	DoorLoadingDock->CallOpenDoorExternal();
}

void AMillTownLevelScriptActor::OnCrowbarTakenHandler()
{
	PlayerUI->ToggleObjective(1, true, true);
	//delay 1s

	PlayerUI->ShowNarrative(true, "No sign of Grundy here in the Town Hall, but I could use this crowbar to enter those houses I passed on the way up the hill.Maybe Grundy lived in one of them and left his Workshop key there.", 8);
	GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);

	//delay 3s

	PlayerUI->SetNewObjective("Search houses for the Workshop key", 1);
	PlayerUI->ToggleObjective(1, false, false);
}

void AMillTownLevelScriptActor::OnKeyTakenHandler()
{
	PlayerUI->CompleteObjective(1);

	//delay 3s
	KeyFound = true;
	PlayerUI->ToggleObjective(1, true, true);
	PlayerUI->SetNewObjective("Return to the Mill", 1);
	PlayerUI->ToggleObjective(1, false, false);


	if (ObjectiveMarkerReturnToMill)
	{
		UE_LOG(LogTemp, Warning, TEXT("dELEGATING TRIGGER"));

		ObjectiveMarkerReturnToMill->Enabled = true;
		ObjectiveMarkerReturnToMill->DisabledOnReach = true;
		ObjectiveMarkerReturnToMill->BoxMarker->OnComponentBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnObjectiveMarkerReached);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The ObjectiveMarkerReturnToMill are not set in the editor!"));

	}
}

void AMillTownLevelScriptActor::OnGearWheelHandler()
{
	PlayerUI->CompleteObjective(1);
	ObjectiveMarkerRetriveGear->Enabled = false;

	//delay 3s

	PlayerUI->ToggleObjective(1, true, true);

	//delay 2s

	PlayerUI->SetNewObjective("Repair the Mill Machinery", 1);
	PlayerUI->ToggleObjective(1, false, false);
	ObjectiveMarkerGearMachine->Enabled = true;
}

void AMillTownLevelScriptActor::OnObjectiveMarkerReached(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ObjectiveMarkerReturnToMill->Enabled = false;

	PlayerUI->CompleteObjective(1);

	//delay 3s

	PlayerUI->ToggleObjective(1, true, true);


	//delay 2s

	PlayerUI->SetNewObjective("RETRIEVE THE GEAR WHEEL FROM THE WORKSHOP", 1);
	ObjectiveMarkerRetriveGear->Enabled = true;

	ObjectiveMarkerReturnToMill->BoxMarker->DestroyComponent();
}