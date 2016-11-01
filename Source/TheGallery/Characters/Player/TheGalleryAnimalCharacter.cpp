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
  float currentSpeed = FMath::Max(GetCharacterMovement()->Velocity.Size(), standardVelocity);
  float newFOVPercent = currentSpeed / (sprintingVelocity * 0.01f);
  float FOVGapPercent = (sprintingFOV - standardFOV) * 0.01f;
  float newFOV = ((standardFOV + (FOVGapPercent * newFOVPercent)) * bIsSprinting) + (standardFOV * !bIsSprinting); // Different if sprinting or not
  GetFollowCamera()->FieldOfView = FMath::Lerp(GetFollowCamera()->FieldOfView, newFOV, FOVSpeed * DeltaTime);
  //DebugLog("", GetFollowCamera()->FieldOfView);
}

// Called to bind functionality to input
void ATheGalleryAnimalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATheGalleryAnimalCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ATheGalleryAnimalCharacter::StopJumping);
  
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

void ATheGalleryAnimalCharacter::Jump()
{
  if (bCanDoDoubleJump && !bDidDoubleJump)
  {
    GetCharacterMovement()->Velocity += FVector(0, 0, 1) * doubleJumpVelocity;
    bCanDoDoubleJump = false;
    bDidDoubleJump = true;
  }
  else
  {
    bCanDoDoubleJump = true;
    ACharacter::Jump();
  }
}

void ATheGalleryAnimalCharacter::StopJumping()
{
  ACharacter::StopJumping();
  bPressedJump = false;
  JumpKeyHoldTime = 0.0f;
}

void ATheGalleryAnimalCharacter::Landed(const FHitResult& Hit)
{
  ACharacter::Landed(Hit);
  bCanDoDoubleJump = false;
  bDidDoubleJump = false;
}