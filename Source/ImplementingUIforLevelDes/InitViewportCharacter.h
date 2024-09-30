// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgetPlayerUI.h"
#include "GameFramework/Character.h"
#include "InitViewportCharacter.generated.h"

UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API AInitViewportCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInitViewportCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UUserWidgetPlayerUI* InitViewportAndReturn();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> UserWidgetPlayerUI;
	
private:
	FTimerHandle MemberTimerHandle;
	UUserWidgetPlayerUI* MyWidgetInstance;
	void HideNarrativeText();
	
};
