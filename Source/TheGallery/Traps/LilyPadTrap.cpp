// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "LilyPadTrap.h"
#include "Character/TheGalleryCharacter.h"

// Sets default values
ALilyPadTrap::ALilyPadTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComp_ = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComp_);

  // Create Collision
  collisionComponent_ = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
  collisionComponent_->SetCollisionProfileName(TEXT("BoxCollision"));
  collisionComponent_->InitBoxExtent(FVector(10, 10, 1));
  collisionComponent_->SetupAttachment(sceneComp_);
  collisionComponent_->OnComponentBeginOverlap.AddDynamic(this, &ALilyPadTrap::OnBeginOverlap);

  // Create Mesh
  mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  mesh_->SetupAttachment(sceneComp_);
}

// Called when the game starts or when spawned
void ALilyPadTrap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALilyPadTrap::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
}

void ALilyPadTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    DebugLog("The Player has hit the Lily Pad Trap");

    //GetWorldTimerManager().SetTimer(sinkTimerHandle_, &ALilyPadTrap::Sink, timeUntilSinking_, false);
  }
  else
  {
    // (Cast to enemy), (if it is an enemy) --> start the sinking timer
  }
}

void ALilyPadTrap::Sink()
{
  DebugLog("Sinking");
  //GetWorldTimerManager().SetTimer(sinkTimerHandle_, &ALilyPadTrap::SinkOf, timeToBeSinked_, false);
}