// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseCharacter.h"


// Sets default values
ATheGalleryBaseCharacter::ATheGalleryBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  FreezedTime = 0.0f;
  Life = 100.0f;
  bCanBeDamaged = true;

  IsDead = false;
  IsFreezed = false;
  IsKnockedBack = false;
}

// Called when the game starts or when spawned
void ATheGalleryBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheGalleryBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  UpdateStatus(DeltaTime);
}

void ATheGalleryBaseCharacter::FreezeCharacter(float Time)
{
  FreezedTime = Time;
  IsFreezed = true;
  CustomTimeDilation = 0.0f;
  DebugLog("Character Freezed");
}

void ATheGalleryBaseCharacter::KnockBackCharacter(float Time)
{
  KnockBackTime = Time;
  IsKnockedBack = true;
  DebugLog("Character Knocked Back");
}

// Called to bind functionality to input
void ATheGalleryBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATheGalleryBaseCharacter::CharacterDeath()
{
  IsDead = true;
}

float ATheGalleryBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
  Life -= DamageAmount;
  if (Life <= 0.0f)
  {
    CharacterDeath();
    return 1.0f;
  }

  return 0.0f;
}

void ATheGalleryBaseCharacter::UpdateStatus(float DeltaTime)
{
  // Update Freeze status
  if (IsFreezed)
  {
    //Delta time is 0 when is freezed
    if (FreezedTime > 0.0f)
      FreezedTime -= GetWorld()->GetDeltaSeconds();
    else
    {
      CustomTimeDilation = 1.0f;
      IsFreezed = false;
      DebugLog("Character Unfreezed");
    }
  }
  if (IsKnockedBack)
  {
    if (KnockBackTime > 0.0f)
      KnockBackTime -= DeltaTime;
    else
    {
      IsKnockedBack = false;
      DebugLog("Character Finish Knock Back");
    }
  }
}
