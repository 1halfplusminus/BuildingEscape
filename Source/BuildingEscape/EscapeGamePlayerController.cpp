// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGamePlayerController.h"



void AEscapeGamePlayerController::BeginPlay(){
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}