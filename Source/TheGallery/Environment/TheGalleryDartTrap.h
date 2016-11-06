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

  // Shoot the Dart trap
  UFUNCTION()
  void ShootDart();

private:
  // Reset the dart
  UFUNCTION()
  void ResetDart();

  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Scene")
  USceneComponent* SceneComponent;

  // Box Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  UBoxComponent* TripwireCollisionComponent;

  // Mesh
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
  UStaticMeshComponent* TripwireMeshComponent;

  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "DartScene")
  USceneComponent* DartsceneComponent;

  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Arrow")
  UArrowComponent* ArrowComponent;

  // Projectile Template
  UPROPERTY(EditAnywhere, Category = "Projectile")
  TSubclassOf<ATheGalleryDart> DartProjectileTemplate;

  // Projectile movement
  UPROPERTY(EditAnywhere, Category = "Dart")
  float DartVelocity = 500.0f;

  // Time to reset the trap
  UPROPERTY(EditAnywhere, Category = "Time")
  float TimeToReset = 1;

  // Reset timer
  FTimerHandle ResetTimerHandle;

  // Initial location of the dart before activate the trap
  FVector DartLocation;

  // Initial rotation of the dart before activate the trap
  FRotator DartRotation;

  // Activated / Deactivated
  bool Activated = false;
};