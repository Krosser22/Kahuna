// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectiles/TheGalleryDart.h"
#include "Components/ArrowComponent.h"
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
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Scene")
  USceneComponent* sceneComponent;

  // Box Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  UBoxComponent* tripwireCollisionComponent;

  // Mesh
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
  UStaticMeshComponent* tripwireMeshComponent;

  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "DartScene")
  USceneComponent* dartsceneComponent;

  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Arrow")
  UArrowComponent* arrowComponent;

  // Projectile Template
  UPROPERTY(EditAnywhere, Category = "Projectile")
  TSubclassOf<ATheGalleryDart> dartProjectileTemplate;

  // Projectile movement
  UPROPERTY(EditAnywhere, Category = "Dart")
  float dartVelocity = 500.0f;

  // Time to reset the trap
  UPROPERTY(EditAnywhere, Category = "Time")
  float timeToReset = 1;

  // Reset timer
  FTimerHandle resetTimerHandle;

  // Initial location of the dart before activate the trap
  FVector dartLocation;

  // Initial rotation of the dart before activate the trap
  FRotator dartRotation;

  // Activated / Deactivated
  bool activated = false;
};