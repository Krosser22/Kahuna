// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryAnimalCharacter.h"

// Sets default values
ATheGalleryAnimalCharacter::ATheGalleryAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATheGalleryAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  //Sprint
  float currentSpeed = GetCharacterMovement()->Velocity.Size();
  if (currentSpeed > standardVelocity)
  {
    float percentage = (currentSpeed - standardVelocity) / (sprintingVelocity - standardVelocity);
    percentage = FMath::Clamp(percentage, 0.0f, 1.0f);
    float FOVGap = sprintingFOV - standardFOV;
    actualFOV = standardFOV + (FOVGap * percentage);
  }
  GetFollowCamera()->FieldOfView = FMath::Lerp(GetFollowCamera()->FieldOfView, actualFOV, FOVSpeed * DeltaTime);
}

// Called to bind functionality to input
void ATheGalleryAnimalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Transform", IE_Pressed, this, &ATheGalleryAnimalCharacter::TransformToHuman);

	// Use parent movement functions (camera movement also)
	InputComponent->BindAxis("MoveForward", this, &ATheGalleryAnimalCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATheGalleryAnimalCharacter::MoveRight);

  // Sprint
  InputComponent->BindAction("Sprint", IE_Pressed, this, &ATheGalleryAnimalCharacter::Sprint);
  InputComponent->BindAction("Sprint", IE_Released, this, &ATheGalleryAnimalCharacter::StopSprinting);
}

void ATheGalleryAnimalCharacter::TransformToHuman()
{
	PossessCharacter(TransformationCharacter, this);
}

void ATheGalleryAnimalCharacter::Sprint()
{
  bIsSprinting = true;
  GetCharacterMovement()->MaxWalkSpeed = sprintingVelocity;
  GetFollowCamera()->FieldOfView = sprintingFOV;
}

void ATheGalleryAnimalCharacter::StopSprinting()
{
  bIsSprinting = false;
  GetCharacterMovement()->MaxWalkSpeed = standardVelocity;
  GetFollowCamera()->FieldOfView = standardFOV;
}

bool ATheGalleryAnimalCharacter::isSprinting()
{
  return bIsSprinting;
}

void ATheGalleryAnimalCharacter::MoveForward(float Value)
{
	ATheGalleryCharacter::MoveForward(Value);
}

void ATheGalleryAnimalCharacter::MoveRight(float Value)
{
	ATheGalleryCharacter::MoveRight(Value);
}