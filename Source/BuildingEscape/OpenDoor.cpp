// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ExtraTerrestreInterface.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	check(PressurePlate != nullptr && "You need a pressure plate to open the door");

	MassToOpen = 5.0f;
	CurrentMass = 0.0f;

	//Init the pressure plate
	PressurePlate->OnActorBeginOverlap.AddUniqueDynamic(this, &UOpenDoor::OnBeginOverlap);
	PressurePlate->OnActorEndOverlap.AddUniqueDynamic(this, &UOpenDoor::OnEndOverlap);
}

void UOpenDoor::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Is the actor a extra terrestre object
	IExtraTerrestreInterface* ExtraTerrestreActor = Cast<IExtraTerrestreInterface>(OtherActor);
	if (ExtraTerrestreActor) {
		ExtraTerrestreActor->StartToGlow();
		UPrimitiveComponent* MeshOfActor = OtherActor->FindComponentByClass<UPrimitiveComponent>();
		if (MeshOfActor)
		{
			CurrentMass += MeshOfActor->GetMass();
		}
	}
	// Check if we can open the door
	if (CurrentMass >= MassToOpen)
	{
		OnOpen.Broadcast();
	}
	else 
	{
		OnClose.Broadcast();
	}
}

void UOpenDoor::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Is the actor a extra terrestre object
	IExtraTerrestreInterface* ExtraTerrestreActor = Cast<IExtraTerrestreInterface>(OtherActor);
	if (ExtraTerrestreActor) {
		ExtraTerrestreActor->StopToGlow();
		UPrimitiveComponent* MeshOfActor = OverlappedActor->FindComponentByClass<UPrimitiveComponent>();
		if (MeshOfActor)
		{
			CurrentMass -= MeshOfActor->GetMass();
		}
	}

}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}