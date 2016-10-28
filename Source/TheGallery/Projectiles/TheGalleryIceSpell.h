// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryProjectile.h"
#include "TheGalleryIceSpell.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryIceSpell : public ATheGalleryProjectile
{
	GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATheGalleryIceSpell();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

private:
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
