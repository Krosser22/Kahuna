// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectiles/TheGallerySpitPoison.h"
#include "Characters/TheGalleryBaseCharacter.h"
#include "TheGalleryBaseEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
  EEnemyType_Basic UMETA(DisplayName = "Basic"),
  EEnemyType_Elite UMETA(DisplayName = "Elite"),
  EEnemyType_Boss UMETA(DisplayName = "Boss")
};

/**
 * 
 */
UCLASS()
class THEGALLERY_API ATheGalleryBaseEnemy : public ATheGalleryBaseCharacter
{
	GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATheGalleryBaseEnemy();

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

  // Return if the spit of poison is on CD
  UFUNCTION(BlueprintCallable, Category = "States")
  bool isSpitPoisonOnCD();

  // Spit a poison projectile
  UFUNCTION(BlueprintCallable, Category = "Attack")
  void spitPoison();

private:
  // Attack Box Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  UBoxComponent* AttackCollisionComponent;

  // Projectile Template
  UPROPERTY(EditAnywhere, Category = "Projectile")
  TSubclassOf<ATheGallerySpitPoison> SpitPoisonProjectileTemplate;

  // The CD of the attack
  UPROPERTY(EditAnywhere, Category = "Attack")
  float AttackCD = 2.0f;

  // The CD of the spit of poison
  UPROPERTY(EditAnywhere, Category = "Attack")
  float SpitPoisonCD = 4.0f;

  // The Damage when attack
  UPROPERTY(EditAnywhere, Category = "Attack")
  float Damage = 9999.0f;

  // The type of enemy
  UPROPERTY(EditAnywhere, Category = "Type")
  EEnemyType Type;

  // If the attack is on CD
  bool IsAttackOnCD = false;

  // If the spit of poison is on CD
  bool IsSpitPoisonOnCD = false;

  // Attack CD timer
  FTimerHandle AttackCDTimerHandle;

  // Spit of poison CD timer
  FTimerHandle SpitPoisonCDTimerHandle;

  // Finish CD Attack
  UFUNCTION()
  void FinishCDAttack();

  // Finish CD Spit of Poison
  UFUNCTION()
  void FinishCDSpitPoison();
};