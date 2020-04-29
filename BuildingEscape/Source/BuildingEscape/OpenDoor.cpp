// Copyright Hyokune 2020

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialAngle = GetOwner()->GetActorRotation().Yaw;
  CurrentAngle = InitialAngle;
  OpenAngle = InitialAngle + OpenAngle;

  if (!PressurePlate)
  {
    UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate set"), *GetOwner()->GetName());
  }

  ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
  {
	  OpenDoor(DeltaTime);
    DoorLastOpened = GetWorld()->GetTimeSeconds();
  }
  else
  {
    if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
    {
      CloseDoor(DeltaTime);
    }
  }
}

void UOpenDoor::OpenDoor(const float& DeltaTime)
{
  FRotator CurrentRotation = GetOwner()->GetActorRotation();
  // UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
  // UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentRotation.Yaw);

  CurrentAngle = FMath::FInterpTo(CurrentAngle, OpenAngle, DeltaTime, DoorOpenSpeed);
  FRotator DoorRotation = CurrentRotation;
  DoorRotation.Yaw = CurrentAngle;
  GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(const float& DeltaTime)
{
  FRotator CurrentRotation = GetOwner()->GetActorRotation();
  // UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
  // UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentRotation.Yaw);

  CurrentAngle = FMath::FInterpTo(CurrentAngle, InitialAngle, DeltaTime, DoorCloseSpeed);
  FRotator DoorRotation = CurrentRotation;
  DoorRotation.Yaw = CurrentAngle;
  GetOwner()->SetActorRotation(DoorRotation);
}