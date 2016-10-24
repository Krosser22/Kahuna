// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryCharacterTransform.h"


// Sets default values
ATheGalleryCharacterTransform::ATheGalleryCharacterTransform()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheGalleryCharacterTransform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheGalleryCharacterTransform::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATheGalleryCharacterTransform::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

