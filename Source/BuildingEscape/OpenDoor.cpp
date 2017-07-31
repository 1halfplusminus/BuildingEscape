// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
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
	if (!IsThereAPressurePlate())
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}

bool UOpenDoor::IsItTimeToCloseTheDoor()
{
	return GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay && LastDoorOpenTime != 0.f;
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation
	GetOwner()->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	LastDoorOpenTime = 0.f;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() >= MassToOpen)
	{
		OpenDoor();
	}
	if (IsItTimeToCloseTheDoor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Door closed"));
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<UPrimitiveComponent*> ComponentsOnPlate;

	if (IsThereAPressurePlate())
	{
		//Find all the overlapping component
		PressurePlate->GetOverlappingComponents(ComponentsOnPlate);
		for (const auto& Component : ComponentsOnPlate)
		{
			TotalMass += Component->GetMass();
		}
	}
	
	return TotalMass;
}

bool UOpenDoor::IsThereAPressurePlate()
{
	return PressurePlate != nullptr;
}
