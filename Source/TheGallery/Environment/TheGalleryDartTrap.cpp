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
  sceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComponent);

  // Create Tripwire Collision
  tripwireCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TripwireBoxCollision"));
  tripwireCollisionComponent->InitBoxExtent(FVector(10, 10, 1));
  tripwireCollisionComponent->SetupAttachment(sceneComponent);
  tripwireCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryDartTrap::OnBeginOverlap);

  // Create Tripwire Mesh
  tripwireMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TripwireMesh"));
  tripwireMeshComponent->SetupAttachment(tripwireCollisionComponent);

  // Create Scene
  dartsceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("DartScene"));
  dartsceneComponent->SetupAttachment(sceneComponent);
  //dartsceneComponent->SetRelativeLocation(tripwireCollisionComponent->RelativeLocation);

  // Create Arrow
  arrowComponent = PCIP.CreateDefaultSubobject<UArrowComponent>(this, TEXT("Arrow"));
  arrowComponent->SetupAttachment(dartsceneComponent);
  //arrowComponent->SetRelativeLocation(dartsceneComponent->RelativeLocation);

  dartVelocity = FVector(-300.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ATheGalleryDartTrap::BeginPlay()
{
	Super::BeginPlay();

  dartLocation = arrowComponent->GetComponentLocation();
  dartRotation = arrowComponent->GetComponentRotation();
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
  GetWorldTimerManager().SetTimer(resetTimerHandle, this, &ATheGalleryDartTrap::ResetDart, timeToReset, false);

  FActorSpawnParameters SpawnParams;
  SpawnParams.Owner = this;
  SpawnParams.Instigator = Instigator;
  ATheGalleryDart *dart = GetWorld()->SpawnActor<ATheGalleryDart>(dartProjectileTemplate, dartLocation, dartRotation, SpawnParams);
  if (dart)
  {
    DebugLog("Working");
  }
  else
  {
    DebugLog("NOT Working");
  }
}

void ATheGalleryDartTrap::ResetDart()
{
  DebugLog("Reset the dart trap");
  activated = false;
}