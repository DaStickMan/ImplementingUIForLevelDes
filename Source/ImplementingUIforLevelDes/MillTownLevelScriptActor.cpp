// Fill out your copyright notice in the Description page of Project Settings.


#include "MillTownLevelScriptActor.h"
#include <Kismet/GameplayStatics.h>

void AMillTownLevelScriptActor::InitializeUI()
{
	PlayerCharacter = Cast<AInitViewportCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerUI = PlayerCharacter->InitViewportAndReturn();
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
	if (TriggerBox)
	{
		// Bind the overlap event
		TriggerBox->OnActorBeginOverlap.AddDynamic(this, &AMillTownLevelScriptActor::OnActorBeginOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TriggerBox is not set in the editor!"));
	}
}

void AMillTownLevelScriptActor::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (PlayerUI && ObjectiveMarkerBridge)
	{
		FTimerHandle TimerHandle;

		UE_LOG(LogTemp, Warning, TEXT("Overlap detected with: %s"), *PlayerUI->GetName());

		PlayerUI->ShowNarrative(true, "The bridge across the river is retracted. Perhaps if I can reach it I can find a way to extend the bridge.", 8);
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AMillTownLevelScriptActor::HideNarrativeText, 8.0f, false);

		
		PlayerUI->CompleteObjective(1);
		
		//2 s

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->ToggleObjective(1, true, true);
			}, 2, false);


		//delay 1s

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				PlayerUI->SetNewObjective("Reach the bridge", 1);
				PlayerUI->ToggleObjective(1, false, false);

				ObjectiveMarkerBridge->Enabled = true;
			}, 3, false);
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
