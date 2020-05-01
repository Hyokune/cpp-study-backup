// Copyright Hyokune 2020

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

  FindPhysicsHandle();
  SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (!PhysicsHandle) { return; }
  if (PhysicsHandle->GrabbedComponent)
  {
    PhysicsHandle->SetTargetLocation(GetPlayerReach());
  }
}

void UGrabber::FindPhysicsHandle()
{
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if (!PhysicsHandle)
  {
    UE_LOG(LogTemp, Error, TEXT("No Physics Handle component found on %s!"), *GetOwner()->GetName());
  }
}

void UGrabber::SetupInputComponent()
{
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if (InputComponent)
  {
    InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("No Input component found on %s!"), *GetOwner()->GetName());
  }
}

void UGrabber::Grab()
{
  FHitResult HitResult = GetFirstPhysicsBodyInReach();
  AActor* ActorHit = HitResult.GetActor();

  if (ActorHit)
  {
    UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

    if (!PhysicsHandle) { return; }
    PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayerReach());
  }
}

void UGrabber::Release()
{
  if (!PhysicsHandle) { return; }
  PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
  FHitResult Hit;
  FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

  GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerPosition(), GetPlayerReach(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

  return Hit;
}

FVector UGrabber::GetPlayerReach() const
{
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

  // Ray-cast out to a certain distance (Reach)
  // DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);
  return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayerPosition() const
{
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

  return PlayerViewPointLocation;
}