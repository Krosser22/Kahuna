// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryGroundSpikeTrap.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryGroundSpikeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryGroundSpikeTrap(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

  // Overlap
  UFUNCTION()
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
  // Scene
  UPROPERTY(Category = "Scene", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  USceneComponent* sceneComp;

  // Box Collision
  UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UBoxComponent* collisionComponent;

  // Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* mesh;
};