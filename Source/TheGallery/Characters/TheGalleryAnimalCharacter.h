// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "TheGalleryCharacter.h"
#include "TheGalleryAnimalCharacter.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryAnimalCharacter : public ATheGalleryCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATheGalleryAnimalCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
