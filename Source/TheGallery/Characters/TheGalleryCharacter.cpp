// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheGallery.h"
#include "TheGalleryCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ATheGalleryCharacter

ATheGalleryCharacter::ATheGalleryCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create Scene Component
	RightButton = CreateDefaultSubobject<USceneComponent>(TEXT("RightCamera"));
	RightButton->SetRelativeLocationAndRotation(FVector(100.0f, -140.0f, 0.0f), FRotator(0.0f, 45.0f, 0.0f));
	RightButton->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	LeftButton = CreateDefaultSubobject<USceneComponent>(TEXT("LeftCamera"));
	LeftButton->SetRelativeLocationAndRotation(FVector(100.0f, 140.0f, 0.0f), FRotator(0.0f, -45.0f, 0.0f));
	LeftButton->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	ForwardBackwardButton = CreateDefaultSubobject<USceneComponent>(TEXT("ForwardBackwardCamera"));
	ForwardBackwardButton->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	ForwardBackwardButton->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Initialize
	CameraSpeed = 3;
	bPossessedNewCharacter = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheGalleryCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &ATheGalleryCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATheGalleryCharacter::MoveRight);
}


void ATheGalleryCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		// Move Camera Forward / Backward
		MoveCamera(GetWorld()->DeltaTimeSeconds, Value, true);
	}
}

void ATheGalleryCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		// Move Camera Right / Left
		MoveCamera(GetWorld()->DeltaTimeSeconds, Value, false);
	}
}

void ATheGalleryCharacter::PossessCharacter(ATheGalleryCharacter* ToPossess, ATheGalleryCharacter* Possessed)
{
	if (ToPossess && Possessed)
	{
		ToPossess->SetActorHiddenInGame(false);
		ToPossess->SetActorEnableCollision(true);
		ToPossess->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		FTransform data = Possessed->FollowCamera->GetRelativeTransform();
		ToPossess->FollowCamera->SetRelativeLocationAndRotation(data.GetLocation(), data.GetRotation());

		Possessed->SetActorEnableCollision(false);
		Possessed->AttachToActor(ToPossess, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Possessed->SetActorHiddenInGame(true);
		GetController()->Possess(ToPossess);

		bPossessedNewCharacter = true;

		//To Do: Reset animation to idle on possess
	}
}

void ATheGalleryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateController();
}

void ATheGalleryCharacter::UpdateController()
{
	if (bPossessedNewCharacter)
	{
		if (Controller != NULL)
		{
			GetController()->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
			bPossessedNewCharacter = false;
		}
	}
}

void ATheGalleryCharacter::MoveCamera(float DeltaTime, float InputValue, bool IsMovingForwardBackward)
{
	if (!IsMovingForwardBackward) 
	{
		// Moving Right
		if (InputValue > 0.0f)
		{
			// Go to a new position and rotation at a specific time when the right button is pressed.
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, RightButton->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, RightButton->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			// Sets them.
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
		// Moving Left
		else if (InputValue < 0.0f)
		{
			// Go to a new position and rotation at a specific time when the left button is pressed.
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, LeftButton->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, LeftButton->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			// Sets them.
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
	}
	else
	{
		// Moving Bakward / Forward
		if (InputValue > 0.0f || InputValue < 0.0f)
		{
			// Go to a new position and rotation at a specific time when the Backward or Forward button are pressed.
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, ForwardBackwardButton->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, ForwardBackwardButton->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			// Sets them.
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
	}
}

