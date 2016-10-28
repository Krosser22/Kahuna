// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Characters/TheGalleryBaseCharacter.h"
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

  FORCEINLINE void SetCharacterOwner(ATheGalleryBaseCharacter* Character) { Owner = Character; }
  FORCEINLINE UStaticMeshComponent* GetMesh() { return Mesh; }
  FORCEINLINE USphereComponent* GetCollisionComponent() { return CollisionComponent; }

protected:
  UFUNCTION()
  virtual void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Sphere Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  USphereComponent* CollisionComponent;

  // Mesh
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
  UStaticMeshComponent* Mesh;

  ATheGalleryBaseCharacter* Owner;

  UPROPERTY(EditAnywhere, Category = "Spawn")
  float Lifetime;

private:
  void UpdateLifeTime(float DeltaTime);
};
