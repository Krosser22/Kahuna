// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryProjectile.h"

// Sets default values
ATheGalleryProjectile::ATheGalleryProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Collision
  CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  CollisionComponent->InitSphereRadius(1.0f);
  RootComponent = CollisionComponent;

  CollisionComponent->bGenerateOverlapEvents = true;
  CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryProjectile::OnBeginOverlap);

  // Create Mesh
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  Mesh->SetupAttachment(CollisionComponent);
  Mesh->AttachParent = CollisionComponent;

  CollisionComponent->SetSimulatePhysics(true);
  //Mesh->SetSimulatePhysics(true);

  Lifetime = 2.0f;
}

// Called when the game starts or when spawned
void ATheGalleryProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  UpdateLifeTime(DeltaTime);
}

void ATheGalleryProjectile::OnBeginOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ATheGalleryProjectile::UpdateLifeTime(float DeltaTime)
{
  if (Lifetime > 0.0f)
    Lifetime -= DeltaTime;
  else
    Destroy();
}

