// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

AMainMenuHUD::AMainMenuHUD()
{
	WidgetInstance = nullptr;
}
void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if(WidgetTemplate)
	{
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);
		if (WidgetInstance != nullptr) {
			WidgetInstance->AddToViewport();
		}
	}
}