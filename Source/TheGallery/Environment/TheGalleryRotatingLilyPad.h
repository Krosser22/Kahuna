// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Environment/TheGalleryLilyPadTrap.h"
#include "GameFramework/Actor.h"
#include "TheGalleryRotatingLilyPad.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryRotatingLilyPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryRotatingLilyPad(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Scene")
  USceneComponent* SceneComponent;

  //The center point
  USphereComponent *Center;

  // The list of lilypads is going to be spawned
  TArray<ATheGalleryLilyPadTrap *> LilyPadsList;

  // Projectile Template
  UPROPERTY(EditAnywhere, Category = "LilyPadTrap")
  TSubclassOf<ATheGalleryLilyPadTrap> LilyPadTrapTemplate;

  // The distance from the center
  UPROPERTY(EditAnywhere, Category = "Distance")
  float DistanceFromCenter = 322.22f;

  // The velocity of rotation of the lilypads
  UPROPERTY(EditAnywhere, Category = "Velocity")
    float VelocityOfRotationOfLilyPads = 0.5f;

  // The velocity of the lilypads
  UPROPERTY(EditAnywhere, Category = "Amount")
  int32 AmountOfLilyPads = 22;
};