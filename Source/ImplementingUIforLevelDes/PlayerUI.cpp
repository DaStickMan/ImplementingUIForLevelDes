// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"
#include "EngineUtils.h"
#include "Engine/Canvas.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

void APlayerUI::BeginPlay()
{
	InitializeUIRefs();
}



void APlayerUI::InitializeUIRefs()
{
	UWorld* World = GetWorld();
	if (!World) return;

	for (TActorIterator<AObjectiveMarker> It(World); It; ++It)
	{
		AObjectiveMarker* Marker = *It;
		ObjectiveMarkers.Add(Marker);
	}
}

void APlayerUI::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas && Canvas->SizeX > 0 && Canvas->SizeY > 0)
	{
		// Get the width and height of the screen (Canvas size)
		sizeX = Canvas->SizeX;
		sizeY = Canvas->SizeY;

		DrawObjectiveMarkers();
	}
}

void APlayerUI::DrawObjectiveMarkers()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();

	for (AObjectiveMarker* Marker: ObjectiveMarkers)
	{
		if (Marker)
		{	
			if (Marker->Enabled) {
				FVector2D ScreenPosition;
				PlayerController->ProjectWorldLocationToScreen(Marker->GetActorLocation(), ScreenPosition);

				screenPosX = FMath::Clamp(ScreenPosition.X, MinScreenPosition, sizeX * 0.95);
				screenPosY = FMath::Clamp(ScreenPosition.Y, MinScreenPosition, sizeY * 0.9);

				/*screenPosX = ScreenPosition.X;
				screenPosY = ScreenPosition.Y;*/

				SetMarkerImage();
				
				//UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %f %f %f %f %d %d"), screenPosX, screenPosY, ObjMarkerScale, ObjMarkerRotation, ScreenPosition.X, ScreenPosition.Y);


				DrawTexture(CurrentTexture, screenPosX, screenPosY, 250, 250, 0, 0, 1, 1, FLinearColor::White, BLEND_Translucent, ObjMarkerScale, false, ObjMarkerRotation);
			}
		}
	}
}

void APlayerUI::SetMarkerImage()
{
	if (IsOffScreenHorizontal())
	{

		UE_LOG(LogTemp, Warning, TEXT("OffScreen Horizontal %f"), screenPosX);

		CurrentTexture = WaypointArrow;
		if (screenPosX <= MinScreenPosition)
		{
			ObjMarkerRotation = 180;
		}
		else 
		{
			ObjMarkerRotation = 0;
		}
	}
	else 
	{
		CurrentTexture = WaypointTexture;
		if (IsOffScreenVertical())
		{
			UE_LOG(LogTemp, Error, TEXT("OffScreen Vertical %f"), screenPosY);

			CurrentTexture = WaypointArrow;
			if (screenPosY <= MinScreenPosition)
			{
				ObjMarkerRotation = -90;
			}
			else 
			{
				ObjMarkerRotation = 90;
			}
		}
		else 
		{
			CurrentTexture = WaypointTexture;
			ObjMarkerRotation = 0;
		}
	}
}

bool APlayerUI::IsOffScreenHorizontal()
{
	return screenPosX >= (sizeX * 0.95) || screenPosX <= MinScreenPosition;
}

bool APlayerUI::IsOffScreenVertical()
{
	return screenPosY >= (sizeY * 0.9) || screenPosY <= MinScreenPosition;
}
