// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "TheGalleryBaseCharacter.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATheGalleryBaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  // Called when the character has no life left
  virtual void CharacterDeath();

  // Called when the character receives damage
  virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

  // The current life of the character
  UPROPERTY(EditAnywhere, Category = "Character Stats")
  float Life;

  bool IsDead;

  // To-Do: more generic stats (player and enemies)...
};
