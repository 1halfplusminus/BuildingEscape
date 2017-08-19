// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UParticleSystemComponent;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtraTerrestreInterface.h"
#include "ExtraTerrestreActor.generated.h"

UCLASS()
class BUILDINGESCAPE_API AExtraTerrestreActor : public AActor, public IExtraTerrestreInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtraTerrestreActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartToGlow() override;
	virtual void StopToGlow() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* Glow;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh;
};
