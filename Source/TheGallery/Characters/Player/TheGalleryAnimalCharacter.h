// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryCharacter.h"
#include "TheGalleryAnimalCharacter.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryAnimalCharacter : public ATheGalleryCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATheGalleryAnimalCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  // Transform to human form
	UFUNCTION(BlueprintCallable, Category = "Transformation")
	void TransformToHuman();

  // Start the sprint
  void Sprint();

  // Stop the sprint
  void StopSprinting();

  UFUNCTION(BlueprintCallable, Category = "State")
  bool isSprinting();

private:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

  // If the AnimalCharacter is sprinting
  bool bIsSprinting = false;

  // The standard velocity
  float standardVelocity = 600.0f;

  // The velocity when sprinting
  float sprintingVelocity = 1800.0f;

  // The standard FOV
  float standardFOV = 90.0f;

  // The FOV when sprinting
  float sprintingFOV = 110.0f;

  // Actual FOV
  float actualFOV = 1.0f;

  // The speed of changing the FOV between standard and sprinting velocity
  float FOVSpeed = 5.0f;
};