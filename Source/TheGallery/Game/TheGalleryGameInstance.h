// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "TheGalleryGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEGALLERY_API UTheGalleryGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Get player total points from the pickups.
	UFUNCTION(BlueprintCallable, Category = PickUp)
	int32 GetPickUpPoints();

	// Set player total points from the pickups.
	UFUNCTION(BlueprintCallable, Category = PickUp)
	void SetPickUpPoints(int32 Points);
	
private:
	// Total points that the player has collected from the pickups
	int32 PickUpPoints;
	
	
};
