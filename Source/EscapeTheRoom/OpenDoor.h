// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h" 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoor();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    UPROPERTY(EditAnywhere)
        ATriggerVolume *Trigger;

    UPROPERTY(EditAnywhere)
        float DoorOpenDuration;

    UPROPERTY(EditAnywhere)
        float OpenDoorMass;

    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnOpen;

    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnClose;

private:
    void OpenDoor();
    void CloseDoor();
    float CalcTotalMassInTriggerVolumn();

    AActor *Owner;
    AActor *DefaultPlayer;
};
