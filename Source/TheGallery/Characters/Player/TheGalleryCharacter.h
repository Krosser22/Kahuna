// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "../TheGalleryBaseCharacter.h"
#include "TheGalleryCharacter.generated.h"

UCLASS(config=Game)
class ATheGalleryCharacter : public ATheGalleryBaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ATheGalleryCharacter();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/**
	 * Called every frame
	 * @param DeltaTime - The time in seconds it took to complete the last frame.
	 */
	virtual void Tick(float DeltaSeconds) override;

  // 
	void SetTransformationCharacter(ATheGalleryCharacter* Character) { TransformationCharacter = Character; }

  // 
	UFUNCTION(BlueprintNativeEvent, Category = "Menu")
	void ActivePauseMenu();

  // 
	void ActivePauseMenu_Implementation();

private:
	/**
	* Move and rotate the camera (FollowCamera)
	* @param DeltaTime - The time in seconds it took to complete the last frame.
	* @param InputValue - Detect what button is the player pressing.
	* @param IsMovingForwardBackward - Know if the camera is going to move right/left or backward/forward.
	*/
	void MoveCamera(float DeltaTime, float InputValue, bool IsMovingForwardBackward);

	//Fixed bug with controller rotation when possessing characters
	void UpdateController();

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

  /**
   * Possess a new character (and unpossess the current one)
   * @param ToPossess - The character that is going to be possessed.
   * @param Possessed - The character that is currently being possessed.
   */
  UFUNCTION(BlueprintCallable, Category = "Transformation")
	void PossessCharacter(ATheGalleryCharacter* ToPossess, ATheGalleryCharacter* Possessed);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  // Called when the character has no life left
  virtual void CharacterDeath() override;

	// New position and rotation when the right button is pressed.
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RightButton;

	// New position and rotation when the left button is pressed.
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* LeftButton;

	// New position and rotation when the forward and backward button are pressed.
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ForwardBackwardButton;

	// Camera Speed
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 CameraSpeed;

  // Reference to the character that is going to be possessed
	ATheGalleryCharacter* TransformationCharacter;
	
	// True when is detected that the character has changed possession
	bool bPossessedNewCharacter;

  // The particle that is going to spawn when a transformation is called
	UPROPERTY(EditAnywhere, Category = "Transformation")
	UParticleSystem* TransformationParticle;
};