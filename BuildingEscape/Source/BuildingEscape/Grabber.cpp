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

  if (PhysicsHandle->GrabbedComponent)
  {
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    // Ray-cast out to a certain distance (Reach)
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

    PhysicsHandle->SetTargetLocation(LineTraceEnd);
  }
}

void UGrabber::FindPhysicsHandle()
{
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if (PhysicsHandle)
  {
    UE_LOG(LogTemp, Warning, TEXT("Physics Handle component found on %s"), *GetOwner()->GetName());
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("No Physics Handle component found on %s!"), *GetOwner()->GetName());
  }
}

void UGrabber::SetupInputComponent()
{
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if (InputComponent)
  {
    UE_LOG(LogTemp, Warning, TEXT("Input component found on %s"), *GetOwner()->GetName());
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
  UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

  // Ray-cast out to a certain distance (Reach)
  FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

  FHitResult HitResult = GetFirstPhysicsBodyInReach();

  if (HitResult.GetActor())
  {
    UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

    PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
  }
}

void UGrabber::Release()
{
  UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
  
  // Remove/Release PhysicsHandle
  PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
  // Get players viewpoint
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;

  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

  // Ray-cast out to a certain distance (Reach)
  FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

  // DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);

  FHitResult Hit;
  FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

  // See what it hits
  GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
  AActor* ActorHit = Hit.GetActor();

  if (ActorHit)
  {
    UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
  }

  return Hit;
}