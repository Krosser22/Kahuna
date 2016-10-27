// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryDartTrap.h"
#include "Characters/TheGalleryCharacter.h"

// Sets default values
ATheGalleryDartTrap::ATheGalleryDartTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComp = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComp);

  // Create Tripwire Collision
  tripwireCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  tripwireCollisionComp->InitBoxExtent(FVector(10, 10, 1));
  tripwireCollisionComp->SetupAttachment(sceneComp);
  tripwireCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryDartTrap::OnBeginOverlap);

  // Create Tripwire Mesh
  tripwireMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TripwireMesh"));
  tripwireMesh->SetupAttachment(tripwireCollisionComp);

  // Create Dart Collision
  dartCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  dartCollisionComp->InitSphereRadius(100);
  dartCollisionComp->SetupAttachment(sceneComp);
  dartCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryDartTrap::OnDartHit);

  // Create Dart Mesh
  dartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DartMesh"));
  dartMesh->SetupAttachment(dartCollisionComp);
  dartMesh->SetEnableGravity(false);
  dartMesh->SetSimulatePhysics(false);

  dartVelocity = FVector(-300.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ATheGalleryDartTrap::BeginPlay()
{
	Super::BeginPlay();

  dartLocation = dartMesh->GetComponentLocation();
}

// Called every frame
void ATheGalleryDartTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheGalleryDartTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Activate the dart trap
    if (!activated)
    {
      DebugLog("The Player has activate the Dart Trap");
      ShootDart();
    }
  }
  else
  {
    DebugLog("NOT PLAYER");
    // TODO: (Cast to enemy), (if it is an enemy) --> kill enemy
  }
}

void ATheGalleryDartTrap::OnDartHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  if (activated)
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
}

void ATheGalleryDartTrap::ShootDart()
{
  DebugLog("Shoot Dart from the dart trap");
  activated = true;
  dartMesh->Activate();
  dartMesh->SetSimulatePhysics(true);
  dartMesh->SetWorldLocationAndRotation(dartLocation, FQuat());
  dartMesh->AddImpulse(dartVelocity);
  GetWorldTimerManager().SetTimer(resetTimerHandle, this, &ATheGalleryDartTrap::ResetDart, timeToReset, false);
}

void ATheGalleryDartTrap::ResetDart()
{
  DebugLog("Reset the dart trap");
  dartMesh->SetWorldLocationAndRotation(dartLocation, FQuat());
  dartMesh->SetSimulatePhysics(false);
  dartMesh->Deactivate();
  activated = false;
}