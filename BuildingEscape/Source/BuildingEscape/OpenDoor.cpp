// Copyright Hyokune 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
  CurrentYaw = InitialYaw;
  TargetYaw = InitialYaw + 90.f;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
  UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
  UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentRotation.Yaw);

  CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 1.6f);
  FRotator DoorRotation = CurrentRotation;
  DoorRotation.Yaw = CurrentYaw;
  GetOwner()->SetActorRotation(DoorRotation);
}
