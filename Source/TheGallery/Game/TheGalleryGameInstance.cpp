// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryGameInstance.h"

int32 UTheGalleryGameInstance::GetPickUpPoints() {
	return PickUpPoints;
}

void UTheGalleryGameInstance::SetPickUpPoints(int32 Points) {
	PickUpPoints = Points;
}

int32 UTheGalleryGameInstance::GetEnemiesPoints() {
	return EnemiesPoints;
}

void UTheGalleryGameInstance::SetEnemiesPoints(int32 Points) {
	EnemiesPoints = Points;
}


