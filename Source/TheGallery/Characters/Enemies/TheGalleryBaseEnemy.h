// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/Enemies/TheGalleryPatrolPoint.h"
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

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called when the character has no life left
  void CharacterDeath() override;

  // Return if it is freezed
  UFUNCTION(BlueprintCallable, Category = "States")
  bool GetIsFreezed();

  // Return if it is knockedback
  UFUNCTION(BlueprintCallable, Category = "States")
  bool GetIsKnockedBack();

  // Return if it is dead
  UFUNCTION(BlueprintCallable, Category = "States")
  bool GetIsDead();

  // Return if the attack is on CD
  UFUNCTION(BlueprintCallable, Category = "States")
  bool GetIsAttackOnCD();

  // Attack
  UFUNCTION(BlueprintCallable, Category = "Attack")
  void Attack();

  // Return if the spit of poison is on CD
  UFUNCTION(BlueprintCallable, Category = "States")
  bool GetIsSpitPoisonOnCD();

  // Spit a poison projectile
  UFUNCTION(BlueprintCallable, Category = "Attack")
  void SpitPoison();

  // Incresase player enemy points
  UFUNCTION(BlueprintCallable, Category = "PickUp")
  void AddPoints();

  // Gets the actual patrol point to move to and the delay that the player should have once arrived to that point
  UFUNCTION(BlueprintCallable, Category = "PatrolPoints")
  void GetPatrolPoint(FVector &position, float &delay);

  // Return if it has patrol points to go
  UFUNCTION(BlueprintCallable, Category = "PatrolPoints")
  bool HasPatrolPoints();

  // Return if the AI is active
  UFUNCTION(BlueprintCallable, Category = "State")
  bool IsActiveStatus();

  // Return if the AI is active
  UFUNCTION(BlueprintCallable, Category = "State")
  void SetActiveStatus(bool active);

  //Reset the AI to the start position
  UFUNCTION(BlueprintCallable, Category = "Reset")
  void Reset();

private:
  // If the AI is active or not
  bool Active = false;

  FVector HomeLocation;

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
  float Damage = 10.0f;

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

  // The velocity of the projectile
  UPROPERTY(EditAnywhere, Category = "SpitPoison")
  float SpitPoisonVelocity = 80.0f;

  // Number of points from one enemy.
  UPROPERTY(EditAnywhere, Category = "Enemy")
  int32 Points = 500;

  // The array of the patrol positions
  UPROPERTY(EditAnywhere, Category = "Patrol")
  TArray<ATheGalleryPatrolPoint*> PatrolPoints;

  // The actual point of the patrol that is going to
  uint8 PatrolPointID = 0;

  // Finish CD Attack
  UFUNCTION()
  void FinishCDAttack();

  // Finish CD Spit of Poison
  UFUNCTION()
  void FinishCDSpitPoison();
};