// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/TheGalleryBaseCharacter.h"
#include "TheGalleryBaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THEGALLERY_API ATheGalleryBaseEnemy : public ATheGalleryBaseCharacter
{
	GENERATED_BODY()

public:
  // Called when the character has no life left
  void CharacterDeath() override;

  UFUNCTION(BlueprintCallable, Category = "States")
  bool isFreezed();

  UFUNCTION(BlueprintCallable, Category = "States")
  bool isKnockedBack();
};