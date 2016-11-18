// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryGameInstance.h"

int32 UTheGalleryGameInstance::GetPickUpPoints()
{
	return PickUpPoints;
}

void UTheGalleryGameInstance::SetPickUpPoints(int32 Points)
{
	PickUpPoints = Points;
}

int32 UTheGalleryGameInstance::GetEnemiesPoints()
{
	return EnemiesPoints;
}

void UTheGalleryGameInstance::SetEnemiesPoints(int32 Points)
{
	EnemiesPoints = Points;
}

int32 UTheGalleryGameInstance::GetTotalPoints()
{
	TotalPoints = PickUpPoints + EnemiesPoints;
	return TotalPoints;
}

void UTheGalleryGameInstance::SetTotalPoints(int32 Points)
{
	TotalPoints = Points;
}

void UTheGalleryGameInstance::SetCheckPoint(FVector location)
{
  CheckPointLocation = location;
  CheckPointLocation.Z += 100;
}

FVector UTheGalleryGameInstance::LastCheckPointLocation()
{
  return CheckPointLocation;
}

float UTheGalleryGameInstance::GetSoundClassVolume(USoundClass * TargetSoundClass)
{
	if (TargetSoundClass)
		return TargetSoundClass->Properties.Volume;

	return 0.0f;
}

void UTheGalleryGameInstance::SetSoundClassVolume(USoundClass * TargetSoundClass, float NewVolume)
{
	if (TargetSoundClass)
		TargetSoundClass->Properties.Volume = NewVolume;
}
