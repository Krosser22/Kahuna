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
	// Get Pick Up Total Points.
	UFUNCTION(BlueprintCallable, Category = PickUp)
	int32 GetPickUpPoints();

	// Set Pick Up Total Points.
	UFUNCTION(BlueprintCallable, Category = PickUp)
	void SetPickUpPoints(int32 Points);
	
private:
	// Pick Up Total Points
	int32 PickUpPoints;
	
	
};
