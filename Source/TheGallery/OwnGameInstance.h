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
	/// Getter
	UFUNCTION(BlueprintCallable, Category = CoconutPickUp)
	int32 GetTotalPointsCoconuts();
	/// Setter
	UFUNCTION(BlueprintCallable, Category = CoconutPickUp)
	void SetTotalPointsCoconuts(int32 points);
	/// Other
	UFUNCTION()
	void IncreaseTotalPointsCoconuts(int32 points);

private:
	UPROPERTY()
	int32 _TotalPointsCoconuts;

	
	
};
