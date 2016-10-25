// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LilyPadTrap.generated.h"

UENUM(BlueprintType) // "BlueprintType" is essential to include
enum class ELilyPadState : uint8
{
  ELilyPadState_Waiting 	UMETA(DisplayName = "Waiting"),
  ELilyPadState_PreparingToSink 	UMETA(DisplayName = "PreparingToSink"),
  ELilyPadState_Sinking 	UMETA(DisplayName = "Sinking"),
  ELilyPadState_WaitingToSinkOff	UMETA(DisplayName = "WaitingToSinkOff"),
  ELilyPadState_SinkingOff	UMETA(DisplayName = "SinkingOff")
};

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
    USceneComponent* sceneComp_;

  // Box Collision
  UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* collisionComponent_;

  // Mesh
  UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* mesh_;

  // Time until the lily pad will start sinking
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float timeUntilSinking_ = 1;

  // Time to be sinked until the lily pad sink off
  UPROPERTY(Category = "Time", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float timeToBeSinked_ = 1;
  
  // State of the lily pad
  ELilyPadState state_;

  // Sink timer
  FTimerHandle sinkTimerHandle_;
};