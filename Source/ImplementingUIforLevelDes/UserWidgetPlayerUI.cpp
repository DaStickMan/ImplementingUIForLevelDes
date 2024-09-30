// Fill out your copyright notice in the Description page of Project Settings.
#include "UserWidgetPlayerUI.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

void UUserWidgetPlayerUI::NativeOnInitialized()
{
	if(Objetive1_text && Objetive2_text)
	{
		Objetive1_text->SetText(FText::FromString(TEXT("Hello, Unreal!")));
		Objetive2_text->SetText(FText::FromString(TEXT("Hello, Unreal!")));
		TextBlock_Narrative->SetRenderOpacity(0);
		Border_Narrative->SetRenderOpacity(0);
		ToggleObjective(1, true, true);
		ToggleObjective(2, true, true);
	}
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
		Objetive1_text->WidgetStyle.SetForegroundColor(FSlateColor(FLinearColor::White)); // white color
		Objetive1_text->SetVisibility(ESlateVisibility::Visible);
	}
	else if(nmObjective == 2)
	{
		Objetive2_text->SetText(FText::FromString(objectiveString));	
		Objetive1_text->WidgetStyle.SetForegroundColor(FSlateColor(FLinearColor::White)); // white color		
		Objetive1_text->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUserWidgetPlayerUI::CompleteObjective(int nmObjective)
{
	if(nmObjective == 1)
	{
		FEditableTextBoxStyle TextBoxStyle = Objetive1_text->WidgetStyle;

		// Set the text color (foreground color)
		TextBoxStyle.SetForegroundColor(FSlateColor(FLinearColor::Green)); // Change to your desired text color

		TextBoxStyle.TextStyle.Font.OutlineSettings.OutlineColor = FLinearColor::Black;
		TextBoxStyle.TextStyle.Font.OutlineSettings.OutlineSize = 10;

		// Apply the new style
		Objetive1_text->WidgetStyle = TextBoxStyle;
	}
	else if(nmObjective == 2)
	{
		FEditableTextBoxStyle TextBoxStyle = Objetive2_text->WidgetStyle;

		// Set the text color (foreground color)
		TextBoxStyle.SetForegroundColor(FSlateColor(FLinearColor::Green)); // Change to your desired text color

		TextBoxStyle.TextStyle.Font.OutlineSettings.OutlineColor = FLinearColor::Black;
		TextBoxStyle.TextStyle.Font.OutlineSettings.OutlineSize = 2;

		// Apply the new style
		Objetive2_text->WidgetStyle = TextBoxStyle;
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

FTextBlockStyle UUserWidgetPlayerUI::GetTextStyleObjectIncomplete()
{
	FTextBlockStyle textBlock;
	
	// Set the font
	textBlock.Font.OutlineSettings.OutlineColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
	textBlock.Font.OutlineSettings.OutlineSize = 2;

	// Set the color and opacity
	//textBlock.SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f))); // white color
	
	return textBlock;
}

FTextBlockStyle UUserWidgetPlayerUI::GetTextStyleObjectComplete()
{
	FTextBlockStyle textBlock;

	// Set the font
	textBlock.Font.OutlineSettings.OutlineColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
	textBlock.Font.OutlineSettings.OutlineSize = 2;

	// Set the color and opacity
	textBlock.SetColorAndOpacity(FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f))); // green color
	
	return textBlock;
}

