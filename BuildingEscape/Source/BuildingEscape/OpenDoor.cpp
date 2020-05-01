// Copyright Hyokune 2020

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

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

	InitialAngle = GetOwner()->GetActorRotation().Yaw;
  CurrentAngle = InitialAngle;
  OpenAngle = InitialAngle + OpenAngle;

  if (!PressurePlate)
  {
    UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate set"), *GetOwner()->GetName());
  }
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (TotalMassOfActors() > MassToOpenDoors)
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

  CurrentAngle = FMath::FInterpTo(CurrentAngle, OpenAngle, DeltaTime, DoorOpenSpeed);

  FRotator DoorRotation = CurrentRotation;
  DoorRotation.Yaw = CurrentAngle;

  GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(const float& DeltaTime)
{
  FRotator CurrentRotation = GetOwner()->GetActorRotation();

  CurrentAngle = FMath::FInterpTo(CurrentAngle, InitialAngle, DeltaTime, DoorCloseSpeed);

  FRotator DoorRotation = CurrentRotation;
  DoorRotation.Yaw = CurrentAngle;

  GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
  float TotalMass = 0.f;

  TArray<AActor*> OverlappingActors;

  if (!PressurePlate) { return TotalMass; }
  PressurePlate->GetOverlappingActors(OUT OverlappingActors);

  for (AActor* Actor : OverlappingActors)
  {
    TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
  }

  return TotalMass;
}