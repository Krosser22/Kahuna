// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LilyPadTrap.generated.h"

UCLASS()
class THEGALLERY_API ALilyPadTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALilyPadTrap(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

  // Overlap
  UFUNCTION()
    void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Sink
  UFUNCTION()
    void Sink();

private:
  // Scene
  UPROPERTY(Category = "Scene", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USceneComponent* sceneComp_;

  // Box Collision
  UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* collisionComponent_;

  // Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* mesh_;

  // Time until the lily pad will start sinking
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float timeUntilSinking_;

  // Time to be sinked until the lily pad sink off
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float timeToBeSinked_;

  // Sink timer
  FTimerHandle sinkTimerHandle_;

  bool isPreparingToSink_;
};