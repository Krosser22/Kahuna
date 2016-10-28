// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseCharacter.h"


// Sets default values
ATheGalleryBaseCharacter::ATheGalleryBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  Life = 100.0f;
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
  CheckDeath(DeltaTime);
}

// Called to bind functionality to input
void ATheGalleryBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATheGalleryBaseCharacter::CharacterDeath()
{

}

void ATheGalleryBaseCharacter::CheckDeath(float DeltaTime)
{
  if (Life <= 0.0f)
    CharacterDeath();
}
