// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


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

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::OnGrabPressed);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::OnGrabReleased);
	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(GetLineEnd());
	}
}

FVector UGrabber::GetLineStart()
{
	FVector Start;
	FRotator Rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, Rotator);
	return Start;
}

FVector UGrabber::GetLineEnd()
{
	FVector Start;
	FRotator Rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, Rotator);
	return Start + Rotator.RotateVector(FVector(200, 0, 0));
}

FHitResult UGrabber::LineTrace()
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetLineStart(),
		GetLineEnd(),
		ECC_PhysicsBody
	);
	return Hit;
}

void UGrabber::OnGrabPressed()
{
	FHitResult Hit = LineTrace();
	AActor *HitActor = Hit.GetActor();
	UPrimitiveComponent *HitComponent = Hit.GetComponent();
	if (HitActor && HitComponent)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitActor->GetActorLocation(), HitActor->GetActorRotation());
		UE_LOG(LogTemp, Display, TEXT("Grab %s"), *HitActor->GetName());
	}
}

void UGrabber::OnGrabReleased()
{
	UPrimitiveComponent *GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("Release %s"), *GrabbedComponent->GetOwner()->GetName());
		PhysicsHandle->ReleaseComponent();
	}
}
