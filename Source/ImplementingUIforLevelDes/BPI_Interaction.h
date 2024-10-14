// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Interaction.generated.h"

UINTERFACE(BlueprintType)
class IMPLEMENTINGUIFORLEVELDES_API UBPI_Interaction : public UInterface
{
    GENERATED_BODY()
};

class IMPLEMENTINGUIFORLEVELDES_API IBPI_Interaction
{
    GENERATED_BODY()

public:
    // This function needs to match the Blueprint signature exactly.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Unlock();
};