// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "OwnGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEGALLERY_API UOwnGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:	
	/// Get number of points obtained.
	UFUNCTION(BlueprintCallable, Category = CoconutPickUp)
	int32 GetTotalPointsCoconuts();
	/// Set number of points obtained.
	UFUNCTION(BlueprintCallable, Category = CoconutPickUp)
	void SetTotalPointsCoconuts(int32 points);
	/// Add points.
	UFUNCTION()
	void IncreaseTotalPointsCoconuts(int32 points);

private:
	/// Number of points obtained.
	UPROPERTY()
	int32 _TotalPointsCoconuts;

	
	
};
