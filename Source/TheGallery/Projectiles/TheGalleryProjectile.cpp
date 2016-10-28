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
  CollisionComponent->bGenerateOverlapEvents = true;
  CollisionComponent->SetupAttachment(RootComponent);
  CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryProjectile::OnBeginOverlap);
  CollisionComponent->SetSimulatePhysics(true);
  CollisionComponent->SetEnableGravity(false);

  // Create Mesh
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  Mesh->SetupAttachment(CollisionComponent);
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

void ATheGalleryProjectile::AddImpulse(FVector impulse)
{
  if (CollisionComponent)
  {
    CollisionComponent->AddImpulse(impulse);
  }
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

