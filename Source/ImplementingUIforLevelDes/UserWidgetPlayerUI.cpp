// Fill out your copyright notice in the Description page of Project Settings.
#include "UserWidgetPlayerUI.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

void UUserWidgetPlayerUI::NativeOnInitialized()
{
}

void UUserWidgetPlayerUI::ShowNarrative(bool show, FString text = TEXT(""), float duration = 0)
{
	if (TextBlock_Narrative && FadeNarrativeBox)
	{
		TextBlock_Narrative->SetText(FText::FromString(text));
		PlayAnimationForward(FadeNarrativeBox, duration);
	}
}

void UUserWidgetPlayerUI::HideNarrative()
{
	if (FadeNarrativeBox)
	{
		PlayAnimationReverse(FadeNarrativeBox);
	}
}

void UUserWidgetPlayerUI::SetNewObjective(FString objectiveString, int nmObjective)
{
	if(nmObjective == 1)
	{
		Objetive1_text->SetText(FText::FromString(objectiveString));
		Objetive1_text->SetTextStyle(NewObjectiveTextStyle);	
		Objetive1_text->SetVisibility(ESlateVisibility::Visible);
	}
	else if(nmObjective == 2)
	{
		Objetive2_text->SetText(FText::FromString(objectiveString));	
		Objetive2_text->SetTextStyle(NewObjectiveTextStyle); 	
		Objetive2_text->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUserWidgetPlayerUI::CompleteObjective(int nmObjective)
{
	if(nmObjective == 1)
	{
		Objetive1_text->SetTextStyle(CompleteObjectiveTextStyle);
	}
	else if(nmObjective == 2)
	{
		Objetive2_text->SetTextStyle(CompleteObjectiveTextStyle);
	}
}

void UUserWidgetPlayerUI::ClearObjectives() const
{
	Objetive1_text->SetText(FText::FromString(TEXT("")));
	Objetive2_text->SetText(FText::FromString(TEXT("")));
}

void UUserWidgetPlayerUI::ToggleObjective(int nmObjective, bool hide, bool clear)
{
	if(clear && hide)
	{
		ClearObjectives();
	}
	else if(hide)
	{
		if(nmObjective == 1)
		{
			Objetive1_text->SetVisibility(ESlateVisibility::Hidden);
		}
		else if(nmObjective == 2)
		{
			Objetive2_text->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		if(nmObjective == 1)
		{
			Objetive1_text->SetVisibility(ESlateVisibility::Visible);
		}
		else if(nmObjective == 2)
		{
			Objetive2_text->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

