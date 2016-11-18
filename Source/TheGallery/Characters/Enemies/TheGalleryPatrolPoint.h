// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TargetPoint.h"
#include "TheGalleryPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class THEGALLERY_API ATheGalleryPatrolPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
  ATheGalleryPatrolPoint();

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Delay")
  float DelayTime = 0.0f;
};