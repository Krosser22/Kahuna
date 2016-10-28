// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryProjectile.h"
#include "TheGalleryDart.generated.h"

UCLASS()
//TO-DO: Inherit from Projectile base class (has the mesh, collision, and spawn life)
class THEGALLERY_API ATheGalleryDart : public ATheGalleryProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryDart();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
  // Overlap
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};