// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraTerrestreActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AExtraTerrestreActor::AExtraTerrestreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root component

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetSimulatePhysics(true);
	CollisionMesh->SetMassOverrideInKg(NAME_None, 1.0f);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionMesh->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetRootComponent(CollisionMesh);

	Glow = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Glow"));
	Glow->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	Glow->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AExtraTerrestreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtraTerrestreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExtraTerrestreActor::StartToGlow()
{
	Glow->Activate();
}

void AExtraTerrestreActor::StopToGlow()
{
	Glow->Deactivate();
}