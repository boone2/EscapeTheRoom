// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector Start;
    FRotator Rotator;
    GetOwner()->GetActorEyesViewPoint(Start, Rotator);
    FVector End = Start + Rotator.Vector() * 100;
    
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0, 0, 10);

    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
        Hit,
        Start,
        End,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
    );
    AActor* Actor = Hit.GetActor();
    if (Actor != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line Hit: %s"), *Actor->GetName());
    }
}

