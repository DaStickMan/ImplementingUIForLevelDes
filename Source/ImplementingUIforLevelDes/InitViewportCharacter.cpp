// Fill out your copyright notice in the Description page of Project Settings.


#include "InitViewportCharacter.h"
#include "UserWidgetPlayerUI.h"

// Sets default values
AInitViewportCharacter::AInitViewportCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInitViewportCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AInitViewportCharacter::HideNarrativeText()
{
	if (MyWidgetInstance)
	{
		MyWidgetInstance->HideNarrative();
		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}
}

// Called every frame
void AInitViewportCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInitViewportCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UUserWidgetPlayerUI* AInitViewportCharacter::InitViewportAndReturn()
{
	if (UserWidgetPlayerUI)
	{
		MyWidgetInstance = CreateWidget<UUserWidgetPlayerUI>(GetWorld(), UserWidgetPlayerUI);
		if (MyWidgetInstance)
		{
			MyWidgetInstance->AddToViewport();
			MyWidgetInstance->ShowNarrative(true, TEXT("I have emerged from the surrounding woods onto the river's edge"), 2);
			GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AInitViewportCharacter::HideNarrativeText, 2.0f, false);
		}
	}

	return MyWidgetInstance;
}

