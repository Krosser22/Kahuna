// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheGallery.h"
#include "TheGalleryCharacter.h"
#include "Game/TheGalleryGameInstance.h"
#include "Characters/Enemies/TheGalleryBaseEnemy.h"

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

// Called when the game starts or when spawned
void ATheGalleryCharacter::BeginPlay()
{
  Super::BeginPlay();

  UTheGalleryGameInstance* GameInstance = Cast<UTheGalleryGameInstance>(GetGameInstance());
  if (GameInstance)
  {
    GameInstance->SetCheckPoint(GetActorLocation());
  }
}

void ATheGalleryCharacter::OnDeathDetected_Implementation()
{

}


//////////////////////////////////////////////////////////////////////////
// Input

void ATheGalleryCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Pause", IE_Pressed, this, &ATheGalleryCharacter::ActivePauseMenu);

	InputComponent->BindAxis("MoveForward", this, &ATheGalleryCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATheGalleryCharacter::MoveRight);
}

void ATheGalleryCharacter::CharacterDeath()
{
  //Reset AI
  /*TSubclassOf<ATheGalleryBaseEnemy> ClassToFind; // Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there
  TArray<AActor*> FoundActors;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
  DebugLog("Actors: ", FoundActors.Num());
  for (int i = 0; i < FoundActors.Num(); i++)
  {
    DebugLog("YEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
    FoundActors[i]->GetInstigatorController()->Reset();
  }*/
  OnDeathDetected();

  DebugLog("Dead");
  //UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

  UTheGalleryGameInstance* GameInstance = Cast<UTheGalleryGameInstance>(GetGameInstance());
  if (GameInstance)
  {
    SetActorLocation(GameInstance->LastCheckPointLocation());
    Life = 100.0f; // TODO: maxlife variable
  }
}

void ATheGalleryCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
    if (!IsBossLevel)
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
    else
      AddMovementInput(ForwardDirection, Value);
  }
}

void ATheGalleryCharacter::MoveRight(float Value)
{
  if ((Controller != NULL) && (Value != 0.0f))
  {
    if (!IsBossLevel)
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
    else
    {
      FVector RightDirection = FVector(-ForwardDirection.Y, ForwardDirection.X, ForwardDirection.Z);
      AddMovementInput(RightDirection, Value);
    }
  }
}

void ATheGalleryCharacter::ActivePauseMenu_Implementation()
{

}

void ATheGalleryCharacter::PossessCharacter(ATheGalleryCharacter* ToPossess, ATheGalleryCharacter* Possessed)
{
	if (ToPossess && Possessed)
	{
    // Show the new character and activate collisions
		ToPossess->SetActorHiddenInGame(false);
		ToPossess->SetActorEnableCollision(true);
		ToPossess->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ToPossess->bPossessedNewCharacter = true;

		//Spawn particles when changing form (have to delete the old one)
		//UGameplayStatics::SpawnEmitterAttached(TransformationParticle, ToPossess->GetMesh());

    // Set the new character camera status to the actual status
		FTransform data = Possessed->FollowCamera->GetRelativeTransform();
		ToPossess->FollowCamera->SetRelativeLocationAndRotation(data.GetLocation(), data.GetRotation());

    // Hide the old character and dissable collisions
		Possessed->SetActorEnableCollision(false);
		Possessed->AttachToActor(ToPossess, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		Possessed->SetActorHiddenInGame(true);

    // Possess new character
		GetController()->Possess(ToPossess);

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
  // Update controller rotation once when the character has been possessed
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

