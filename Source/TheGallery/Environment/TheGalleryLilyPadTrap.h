// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryLilyPadTrap.generated.h"

UENUM(BlueprintType) // "BlueprintType" is essential to include
enum class ELilyPadState : uint8
{
  ELilyPadStateWaiting 	UMETA(DisplayName = "Waiting"),
  ELilyPadStatePreparingToSink 	UMETA(DisplayName = "PreparingToSink"),
  ELilyPadStateSinking 	UMETA(DisplayName = "Sinking"),
  ELilyPadStateWaitingToSinkOff	UMETA(DisplayName = "WaitingToSinkOff"),
  ELilyPadStateSinkingOff	UMETA(DisplayName = "SinkingOff")
};

UCLASS()
class THEGALLERY_API ATheGalleryLilyPadTrap : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATheGalleryLilyPadTrap(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

  // Overlap
  UFUNCTION()
  void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

  // Sink
  UFUNCTION()
  void Sink();

  // Waiting To Sink Off
  UFUNCTION()
  void WaitingToSinkOff();

  // Sink off
  UFUNCTION()
  void SinkOff();

  // Finish of sink off
  UFUNCTION()
  void FinishOfSinkOff();

private:
  // Scene
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Scene")
  USceneComponent* sceneComponent;

  // Box Collision
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Collision")
  UBoxComponent* collisionComponent;

  // Mesh
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
  UStaticMeshComponent* meshComponent;

  // Sink timer
  FTimerHandle sinkTimerHandle;

  // State of the lily pad
  ELilyPadState state;

  // Time until the lily pad will start sinking
  UPROPERTY(EditAnywhere, Category = "Time")
  float timeUntilSinking = 0.6f;

  // Time to be sinked until the lily pad sink off
  UPROPERTY(EditAnywhere, Category = "Time")
  float timeToBeSinked = 0.6f;

  //Speed of sink the trap
  UPROPERTY(EditAnywhere, Category = "Time")
  float speedOfSink = 0.1f;

  //Distance to sink the trap
  UPROPERTY(EditAnywhere, Category = "Distance")
  float distanceToSink = -22.0f;

  // Damage of the trap
  UPROPERTY(EditAnywhere, Category = "Damage")
  float damage = 9999;

  // Alpha of lerp
  float alpha = 0;
};