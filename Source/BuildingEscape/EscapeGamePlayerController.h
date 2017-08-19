// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EscapeGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AEscapeGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
};
