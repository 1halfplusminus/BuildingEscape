// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
UCLASS()
class BUILDINGESCAPE_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float);

	/** Handles movement, left and right */
	void MoveRight(float);

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere,Category = "Camera")
	/** First person camera */
	UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(VisibleDefaultsOnly,Category = "Mesh")
	// First-person mesh (arms), visible only to the owning player.
	USkeletalMeshComponent* FirstPersonMesh;
};
