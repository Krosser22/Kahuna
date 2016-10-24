// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "GroundSpikeTrap.h"
#include "Characters/TheGalleryCharacter.h"

// Sets default values
AGroundSpikeTrap::AGroundSpikeTrap(const class FObjectInitializer& PCIP)
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComp_ = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComp_);

  // Create Collision
  collisionComponent_ = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  collisionComponent_->InitBoxExtent(FVector(10, 10, 1));
  collisionComponent_->SetupAttachment(sceneComp_);
  collisionComponent_->OnComponentBeginOverlap.AddDynamic(this, &AGroundSpikeTrap::OnBeginOverlap);

  // Create Mesh
  mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  mesh_->SetupAttachment(sceneComp_);
}

// Called when the game starts or when spawned
void AGroundSpikeTrap::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void AGroundSpikeTrap::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void AGroundSpikeTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Kill character
    DebugLog("The Player has hit the Ground Spike Trap");
  }
  else
  {
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}