// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheGallery.h"
#include "TheGalleryCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ATheGalleryCharacter

ATheGalleryCharacter::ATheGalleryCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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

	bIsAPressed = false;
	bIsDPressed = false;
	bIsSPressed = false;
	bIsWPressed = false;

	D = CreateDefaultSubobject<USceneComponent>(TEXT("CameraD"));
	D->SetRelativeLocationAndRotation(FVector(100.0f, -140.0f, 0.0f), FRotator(0.0f, 45.0f, 0.0f));
	D->SetupAttachment(FollowCamera);

	A = CreateDefaultSubobject<USceneComponent>(TEXT("CameraA"));
	A->SetRelativeLocationAndRotation(FVector(100.0f, 140.0f, 0.0f), FRotator(0.0f, -45.0f, 0.0f));
	A->SetupAttachment(FollowCamera);

	WS = CreateDefaultSubobject<USceneComponent>(TEXT("CameraWS"));
	WS->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	WS->SetupAttachment(FollowCamera);

	CameraSpeed = 3;
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

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	/*InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATheGalleryCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATheGalleryCharacter::LookUpAtRate);*/

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ATheGalleryCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ATheGalleryCharacter::TouchStopped);
}


void ATheGalleryCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ATheGalleryCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ATheGalleryCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheGalleryCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATheGalleryCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		if (Value > 0)
		{
			bIsWPressed = true;
			bIsAPressed = bIsSPressed = bIsDPressed = false;
		}
		else 
		{
			bIsSPressed = true;
			bIsAPressed = bIsDPressed = bIsWPressed = false;
		}
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATheGalleryCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		if (Value > 0)
		{
			bIsDPressed = true;
			bIsAPressed = bIsSPressed = bIsWPressed = false;
		}
		else
		{
			bIsAPressed = true;
			bIsSPressed = bIsWPressed = bIsDPressed = false;
		}

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATheGalleryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCamera(DeltaTime);
}

void ATheGalleryCharacter::MoveCamera(float DeltaTime)
{
	if (bIsDPressed) 
	{
		if (!bIsWPressed | !bIsAPressed | !bIsSPressed) 
		{
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, D->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, D->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
	}
	else if (bIsAPressed) 
	{
		if (!bIsWPressed | !bIsDPressed | !bIsSPressed)
		{
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, A->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, A->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
	}
	else if(bIsWPressed | bIsSPressed) {

		if (!bIsAPressed | !bIsDPressed)
		{
			FVector Translation = FMath::Lerp(FollowCamera->RelativeLocation, WS->RelativeLocation, DeltaTime * CameraSpeed);
			FRotator Rotation = FMath::Lerp(FollowCamera->RelativeRotation, WS->RelativeRotation, (DeltaTime * CameraSpeed) / CameraSpeed);
			FollowCamera->SetRelativeLocationAndRotation(Translation, Rotation);
		}
	}
}
