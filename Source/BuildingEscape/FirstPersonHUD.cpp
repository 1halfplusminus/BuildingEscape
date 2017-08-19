// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonHUD.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "Engine/Texture2D.h"


AFirstPersonHUD::AFirstPersonHUD()
{
	/** Init the Crosshair texture at null must be set up in blueprint */
	CrosshairTex = nullptr;
}

void AFirstPersonHUD::DrawHUD()
{
	/** The texture for the crosshair must be overrided in blueprint */
	check(CrosshairTex != nullptr && "Did you forget set a crosshair texture ?")
	
	Super::DrawHUD();

	/** find the center of the canvas */
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	/** compute the crosshair position to be in the middle of the screen */
	const FVector2D CrosshairDrawnPosition(Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f));
	/** draw the crosshair */
	FCanvasTileItem TileCrosshairItem(CrosshairDrawnPosition,CrosshairTex->Resource,FLinearColor::White);
	TileCrosshairItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileCrosshairItem);
}