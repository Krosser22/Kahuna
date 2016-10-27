// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryDartTrap.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryDartTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryDartTrap(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

  // Overlap with the tripwire
  UFUNCTION()
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Overlap with the dart
  UFUNCTION()
  void OnDartHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Shoot the Dart trap
  UFUNCTION()
  void ShootDart();

private:
  // Reset the dart
  UFUNCTION()
  void ResetDart();

  // Scene
  UPROPERTY(Category = "Scene", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  USceneComponent* sceneComp;

  // Tripwire Collision
  UPROPERTY(Category = "BoxCollision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UBoxComponent* tripwireCollisionComp;

  // Dart collision
  UPROPERTY(Category = "SphereCollision", VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
  USphereComponent* dartCollisionComp;

  // Tripwire Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* tripwireMesh;

  // Dart Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* dartMesh;

  // Projectile movement
  UPROPERTY(Category = "Dart", EditAnywhere)
  FVector dartVelocity;

  // Activated / Deactivated
  bool activated = false;

  // Initial location of the dart before activate the trap
  FVector dartLocation;

  // Reset timer
  FTimerHandle resetTimerHandle;

  //Time to reset the trap
  float timeToReset = 1;

  UPROPERTY(EditAnywhere, Category = "Projectile")
  TSubclassOf<AActor> ProjectileTemplate;
};