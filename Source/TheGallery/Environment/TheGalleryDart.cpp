// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryDart.h"
#include "Characters/TheGalleryCharacter.h"

// Sets default values
ATheGalleryDart::ATheGalleryDart(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComponent);

  // Create Collision
  collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  collisionComponent->InitSphereRadius(1.0f);
  collisionComponent->SetupAttachment(sceneComponent);
  collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryDart::OnBeginOverlap);

  // Create Mesh
  meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  meshComponent->SetupAttachment(collisionComponent);
}

// Called when the game starts or when spawned
void ATheGalleryDart::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryDart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheGalleryDart::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Kill character
    DebugLog("The Player has hit the Dart");
  }
  else
  {
    DebugLog("NOT A PLAYER");
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}