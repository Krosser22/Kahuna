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

  // Return if it is freezed
  UFUNCTION(BlueprintCallable, Category = "States")
  bool isFreezed();

  // Return if it is knockedback
  UFUNCTION(BlueprintCallable, Category = "States")
  bool isKnockedBack();

  // Return if it is dead
  UFUNCTION(BlueprintCallable, Category = "States")
  bool isDead();

  // Return if the attack is on CD
  UFUNCTION(BlueprintCallable, Category = "States")
  bool isAttackOnCD();

  // Attack
  UFUNCTION(BlueprintCallable, Category = "Attack")
  void attack();

private:
  // Finish CD Attack
  UFUNCTION()
  void FinishCDAttack();

  // The CD of the attack
  UPROPERTY(EditAnywhere, Category = "Attack")
  float attackCD = 2.0f;

  bool IsAttackOnCD = false;

  // Attack CD timer
  FTimerHandle attackCDTimerHandle;
};