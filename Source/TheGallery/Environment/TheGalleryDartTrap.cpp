// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryDartTrap.h"
#include "Characters/TheGalleryBaseCharacter.h"

// Sets default values
ATheGalleryDartTrap::ATheGalleryDartTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(SceneComponent);

  // Create Tripwire Collision
  TripwireCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TripwireBoxCollision"));
  TripwireCollisionComponent->InitBoxExtent(FVector(10, 10, 1));
  TripwireCollisionComponent->SetupAttachment(SceneComponent);
  TripwireCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryDartTrap::OnBeginOverlap);

  // Create Tripwire Mesh
  TripwireMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TripwireMesh"));
  TripwireMeshComponent->SetupAttachment(TripwireCollisionComponent);

  // Create Scene
  DartsceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("DartScene"));
  DartsceneComponent->SetupAttachment(SceneComponent);

  // Create Arrow
  ArrowComponent = PCIP.CreateDefaultSubobject<UArrowComponent>(this, TEXT("Arrow"));
  ArrowComponent->SetupAttachment(DartsceneComponent);
}

// Called when the game starts or when spawned
void ATheGalleryDartTrap::BeginPlay()
{
	Super::BeginPlay();

  DartLocation = ArrowComponent->GetComponentLocation();
  DartRotation = ArrowComponent->GetComponentRotation();
}

// Called every frame
void ATheGalleryDartTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheGalleryDartTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryBaseCharacter* Character = Cast<ATheGalleryBaseCharacter>(OtherActor);

  if (Character && !Activated)
  {
    // The Player has activate the Dart Trap
    ShootDart();
  }
}

void ATheGalleryDartTrap::ShootDart()
{
  // Shoot Dart from the dart trap
  Activated = true;
  GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &ATheGalleryDartTrap::ResetDart, TimeToReset, false);

  FActorSpawnParameters SpawnParams;
  SpawnParams.Owner = this;
  SpawnParams.Instigator = Instigator;
  ATheGalleryDart *dart = GetWorld()->SpawnActor<ATheGalleryDart>(DartProjectileTemplate, DartLocation, DartRotation, SpawnParams);
  if (dart)
  {
    dart->SetLifeSpan(1.0f);
    dart->AddImpulse(DartRotation.Vector() * DartVelocity);
  }
}

void ATheGalleryDartTrap::ResetDart()
{
  // Reset the dart trap
  Activated = false;
}