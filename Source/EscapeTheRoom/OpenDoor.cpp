// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
    DefaultPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    float mass = CalcTotalMassInTriggerVolumn();

    if (mass >= OpenDoorMass)
    {
        OpenDoor();
    }
    else
    {
        CloseDoor();
    }
}

void UOpenDoor::OpenDoor()
{
    OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor()
{
    OnClose.Broadcast();
}

float UOpenDoor::CalcTotalMassInTriggerVolumn()
{
    if (nullptr == Trigger)
        return 0;

    TArray<AActor*> OverlappingActors;
    Trigger->GetOverlappingActors(OUT OverlappingActors, AActor::StaticClass());
    float totalMass = 0;
    for (const AActor* actor : OverlappingActors)
    {
        auto component = actor->FindComponentByClass<UPrimitiveComponent>();
        float mass = component->GetMass();
        totalMass += mass;
    }
    return totalMass;
}

