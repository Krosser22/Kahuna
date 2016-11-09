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

	/**
	* Get player total points from the pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
	int32 GetPickUpPoints();

	/**
	* Set player total points from the pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
	void SetPickUpPoints(int32 Points);

	/**
	* Get player total points from the enemies.
	*/
	UFUNCTION(BlueprintCallable, Category = Enemy)
	int32 GetEnemiesPoints();

	/**
	* Set player total points from enemies.
	*/
	UFUNCTION(BlueprintCallable, Category = Enemy)
	void SetEnemiesPoints(int32 Points);

	/**
	* Get player total points from enemies + pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = Enemy)
	int32 GetTotalPoints();

	/**
	* Set player total points from  enemies + pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = Enemy)
	void SetTotalPoints(int32 Points);
	
	
private:
	// Points from the pickups
	int32 PickUpPoints;
	// Points from the enemies
	int32 EnemiesPoints;
	// Points from both
	int32 TotalPoints;
	
	
};
