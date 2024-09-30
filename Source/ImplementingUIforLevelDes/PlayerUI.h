// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectiveMarker.h"
#include "Algo/Reverse.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/HUD.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API APlayerUI : public AHUD
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* WaypointTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* WaypointArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ObjMarkerScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ObjMarkerRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinScreenPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

private:
	void DrawObjectiveMarkers();
	void InitializeUIRefs();
	void SetMarkerImage();
	bool IsOffScreenHorizontal();
	bool IsOffScreenVertical();

	TArray<AObjectiveMarker*> FoundMarkers;

	int32 sizeX;
	int32 sizeY;

	UTexture* CurrentTexture;

	float screenPosX;
	float screenPosY;

	float markerRotation;

	TArray<AObjectiveMarker*> ObjectiveMarkers;
};
