// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryGroundSpikeTrap.h"
#include "Characters/TheGalleryCharacter.h"

// Sets default values
ATheGalleryGroundSpikeTrap::ATheGalleryGroundSpikeTrap(const class FObjectInitializer& PCIP)
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComponent);

  // Create Collision
  collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  collisionComponent->InitBoxExtent(FVector(10, 10, 1));
  collisionComponent->SetupAttachment(sceneComponent);
  collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryGroundSpikeTrap::OnBeginOverlap);

  // Create Mesh
  meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  meshComponent->SetupAttachment(collisionComponent);
}

// Called when the game starts or when spawned
void ATheGalleryGroundSpikeTrap::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ATheGalleryGroundSpikeTrap::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ATheGalleryGroundSpikeTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Kill character
    DebugLog("The Player has hit the Ground Spike Trap");
  }
  else
  {
    DebugLog("NOT A PLAYER");
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}