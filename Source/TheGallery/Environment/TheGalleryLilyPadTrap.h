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
  UPROPERTY(Category = "Scene", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  USceneComponent* sceneComp;

  // Box Collision
  UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UBoxComponent* collisionComponent;

  // Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* mesh;

  // Time until the lily pad will start sinking
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  float timeUntilSinking = 1;

  // Time to be sinked until the lily pad sink off
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  float timeToBeSinked = 1;
  
  // State of the lily pad
  ELilyPadState state;

  // Sink timer
  FTimerHandle sinkTimerHandle;
};