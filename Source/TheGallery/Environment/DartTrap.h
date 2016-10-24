// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DartTrap.generated.h"

UCLASS()
class THEGALLERY_API ADartTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADartTrap(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

  // Overlap
  UFUNCTION()
    void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Overlap
  UFUNCTION()
    void OnDartHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Overlap
  UFUNCTION()
    void ShootDart();

private:
  // Scene
  UPROPERTY(Category = "Scene", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USceneComponent* sceneComp_;

  // Tripwire Collision
  UPROPERTY(Category = "BoxCollision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* tripwireCollisionComp_;

  // Dart collision
  UPROPERTY(Category = "SphereCollision", VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
    USphereComponent* dartCollisionComp_;

  // Tripwire Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* tripwireMesh_;

  // Dart Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* dartMesh_;

  // Projectile movement
  UPROPERTY(Category = "ProjectileMovement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* dartProjectileMovement_;

  // Projectile movement
  UPROPERTY(Category = "Dart", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float dartSpeed_;

  bool activated_ = false;
};