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

	// Save the location of the last checkpoint touched
	void SetCheckPoint(FVector location);

	// Return the last CheckPoint location
	FVector LastCheckPointLocation();

	/**
	* Gets the volume value from a specific Sound Class.
	* @param TargetSoundClass - Sound class.
	*/
	UFUNCTION(BlueprintCallable, Category = Sound)
	float GetSoundClassVolume(USoundClass* TargetSoundClass);

	/**
	* Sets the volume value from a specific Sound Class.
	* @param TargetSoundClass - Sound class.
	* @param NewVolume - Desired volume (minimum is 0 and maximum is 1).
	*/
	UFUNCTION(BlueprintCallable, Category = Sound)
	void SetSoundClassVolume(USoundClass* TargetSoundClass, float NewVolume);

	/**
	* Set player total points from enemies.
	*/
	UFUNCTION(BlueprintCallable, Category = Score)
	void SetNumberOfPickUps(int32 Points);

	/**
	* Get player total points from enemies + pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = Score)
	int32 GetNumberOfPickUps();

	/**
	* Set player total points from enemies.
	*/
	UFUNCTION(BlueprintCallable, Category = Score)
	void SetNumberOfEnemies(int32 Points);

	/**
	* Get player total points from enemies + pickups.
	*/
	UFUNCTION(BlueprintCallable, Category = Score)
	int32 GetNumberOfEnemies();


private:
	// Points from the pickups
	int32 PickUpPoints;

	// Points from the enemies
	int32 EnemiesPoints;

	// Points from both
	int32 TotalPoints;

	// The location of the active's CheckPoint
	FVector CheckPointLocation;

	// Points from both
	int32 TotalPickUps;

	// Points from both
	int32 TotalEnemies;
};