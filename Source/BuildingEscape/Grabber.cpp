// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"

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
	FindPhysicsHandleComponent();
	FindInputComponent();
}

void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	// Look for attached Physics Handle
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicHandle)
	{
		// Phycics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("grab pressed"))
	auto HitResult = GetFirstPhysicsBodyReach();
	auto ComponentToGrap = HitResult.GetComponent();
	// LINE TRACE and reach any actors with physics body collision channel set
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("We hit %s"), *HitResult.GetActor()->GetName())
		PhysicHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrap,
			NAME_None,
			ComponentToGrap->GetOwner()->GetActorLocation(),
			FRotator(0.0f,0.0f,0.0f)
		);
	}
	// If we hit something attach a physics handle

	// TODO attach physics handle
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("grab release"))
	PhysicHandle->ReleaseComponent();
	// TODO release physics handle
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// If the physics handle is attached
	if (PhysicHandle->GrabbedComponent)
	{
		FVector Location;
		FRotator Rotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

		FVector LineTraceEnd = Location + Rotation.Vector() * Reach;
		// move the object that we're holding
		PhysicHandle->SetTargetLocation(LineTraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyReach()
{
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

	FVector LineTraceEnd = Location + Rotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		Location,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
	// Line-trace (AKA Ray-cast) out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult,
		Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	return HitResult;
}

