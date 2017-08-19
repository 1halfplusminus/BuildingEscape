// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstPersonHUD.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AFirstPersonHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AFirstPersonHUD();

	/** Primary draw call for HUD */
	virtual void DrawHUD() override;
private:
	/** Texture of the crosshair set in blueprint */
	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* CrosshairTex;
};
