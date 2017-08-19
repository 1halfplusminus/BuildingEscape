// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonCharacter.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.0f);

	// Initialise the camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera Component"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	// Allow the pawn to control camera rotation.
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Create a first person mesh and attach it to the camera
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->bCastDynamicShadow = false;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/** Mouvement **/
	PlayerInputComponent->BindAxis(FName("MoveRight"),this,&AFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AFirstPersonCharacter::MoveForward);
	/** Camera action */
	PlayerInputComponent->BindAxis(FName("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &APawn::AddControllerPitchInput);
	
}
void AFirstPersonCharacter::MoveRight(float ScaleValue) 
{
	
	if (ScaleValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), ScaleValue);
	}
}

void AFirstPersonCharacter::MoveForward(float ScaleValue)
{
	if (ScaleValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), ScaleValue);
	}
}