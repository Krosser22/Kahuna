// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "TheGalleryCharacter.generated.h"

UCLASS(config=Game)
class ATheGalleryCharacter : public ACharacter
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

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/**
	 * Called every frame
	 * @param DeltaTime - The time in seconds it took to complete the last frame.
	 */
	virtual void Tick(float DeltaSeconds) override;

	void SetTransformationCharacter(ATheGalleryCharacter* Character) { TransformationCharacter = Character; }

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

	UFUNCTION(BlueprintCallable, Category = "Transformation")
	void PossessCharacter(ATheGalleryCharacter* ToPossess, ATheGalleryCharacter* Possessed);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

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

	ATheGalleryCharacter* TransformationCharacter;
	
	bool bPossessedNewCharacter;
};

