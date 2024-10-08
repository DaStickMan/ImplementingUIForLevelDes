// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveMarker.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

// Sets default values
AObjectiveMarker::AObjectiveMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectiveMarker::BeginPlay()
{
	Super::BeginPlay();	

    ObjectiveMarker = Cast<UBillboardComponent>(GetDefaultSubobjectByName(TEXT("ObjMarker")));
    BillboardMarker = Cast<UBillboardComponent>(GetDefaultSubobjectByName(TEXT("Billboard")));
    BoxMarker = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("Box")));

    if (UseTrigger)
    {
        BoxMarker->SetBoxExtent(TriggerSize);
    }
    else 
    {
        BoxMarker->DestroyComponent();
    }

    BoxMarker->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveMarker::OnBoxOverlap);

    SetIsTemporarilyHiddenInEditor(Enabled);

}

// Called every frame
void AObjectiveMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectiveMarker::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (NextObjectMarker)
    {
        NextObjectMarker->Enabled = true;
        Enabled = false;
    }
}

