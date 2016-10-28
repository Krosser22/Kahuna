// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryProjectile.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

  void AddImpulse(FVector impulse);

protected:
  virtual void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Sphere Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  USphereComponent* CollisionComponent;

  // Mesh
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
  UStaticMeshComponent* Mesh;

private:
  void UpdateLifeTime(float DeltaTime);

  UPROPERTY(EditAnywhere, Category = "Spawn")
  float Lifetime;
};
