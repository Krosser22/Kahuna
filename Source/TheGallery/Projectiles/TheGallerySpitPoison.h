// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectiles/TheGalleryProjectile.h"
#include "TheGallerySpitPoison.generated.h"

/**
 * 
 */
UCLASS()
class THEGALLERY_API ATheGallerySpitPoison : public ATheGalleryProjectile
{
	GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATheGallerySpitPoison();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

private:
  // Overlap
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

  // Damage of the trap
  UPROPERTY(EditAnywhere, Category = "Damage")
  float Damage = 9999;
};