// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "UserWidgetPlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class IMPLEMENTINGUIFORLEVELDES_API UUserWidgetPlayerUI : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* Objetive1_text;
;
    UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* Objetive2_text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Narrative;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Narrative;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeNarrativeBox = nullptr;
	
	virtual void NativeOnInitialized() override;
	void SetNewObjective(FString objective, int nmObjective);
	void CompleteObjective(int nmObjective);
	void ClearObjectives() const;
	void ToggleObjective(int nmObjective, bool hide, bool clear);
	void ShowNarrative(bool show, FString text, float duration);
	void HideNarrative();
private:
	FString Text1;
	FString Text2;

	FTextBlockStyle GetTextStyleObjectIncomplete();
	FTextBlockStyle GetTextStyleObjectComplete();
};
