// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "DartTrap.h"
#include "Character/TheGalleryCharacter.h"

// Sets default values
ADartTrap::ADartTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComp_ = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComp_);

  // Create Tripwire Collision
  tripwireCollisionComp_ = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  tripwireCollisionComp_->InitBoxExtent(FVector(10, 10, 1));
  tripwireCollisionComp_->SetupAttachment(sceneComp_);
  tripwireCollisionComp_->OnComponentBeginOverlap.AddDynamic(this, &ADartTrap::OnBeginOverlap);

  // Create Tripwire Mesh
  tripwireMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TripwireMesh"));
  tripwireMesh_->SetupAttachment(sceneComp_);

  // Create Dart Collision
  dartCollisionComp_ = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  dartCollisionComp_->InitSphereRadius(10);
  dartCollisionComp_->SetupAttachment(sceneComp_);
  dartCollisionComp_->OnComponentBeginOverlap.AddDynamic(this, &ADartTrap::OnDartHit);

  // Create Dart Mesh
  dartMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DartMesh"));
  dartMesh_->SetupAttachment(dartCollisionComp_);

  //Create Projectile
  dartProjectileMovement_ = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Projectile"));
  dartProjectileMovement_->UpdatedComponent = dartCollisionComp_;
  dartProjectileMovement_->Deactivate();
}

// Called when the game starts or when spawned
void ADartTrap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADartTrap::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
}

void ADartTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Activate the dart trap
    DebugLog("The Player has activate the Dart Trap");

    //if (!activated_) ShootDart();
  }
  else
  {
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}

void ADartTrap::OnDartHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Kill character
    DebugLog("The Player has been hit by the Dart trap");
  }
  else
  {
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}

void ADartTrap::ShootDart()
{
  DebugLog("Shoot Dart from the dart trap");
  activated_ = true;
  dartProjectileMovement_->Activate();
  dartProjectileMovement_->Velocity = FVector(300.0f, 0.0f, 0.0f);
}