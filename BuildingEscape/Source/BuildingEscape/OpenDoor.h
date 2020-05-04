// Copyright Hyokune 2020

#pragma once

#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
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
  void OpenDoor(const float& DeltaTime);
  void CloseDoor(const float& DeltaTime);
  float TotalMassOfActors() const;
  void FindPressurePlate();
  void FindAudioComponent();

  bool OpenDoorSound = false;
  bool CloseDoorSound = true;

private:
  float InitialAngle;
  float CurrentAngle;

  UPROPERTY(EditAnywhere)
  float MassToOpenDoors = 50.f;

  UPROPERTY(EditAnywhere)
  float OpenAngle = 90.f;

  float DoorLastOpened = 0.f;

  UPROPERTY(EditAnywhere)
  float DoorCloseDelay = 0.5f;

  UPROPERTY(EditAnywhere)
  float DoorOpenSpeed = 1.6f;

  UPROPERTY(EditAnywhere)
  float DoorCloseSpeed = 2.f;

  UPROPERTY(EditAnywhere)
  ATriggerVolume* PressurePlate = nullptr;

  UPROPERTY(EditAnywhere)
  UAudioComponent* AudioComponent = nullptr;
};