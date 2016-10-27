// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "DartTrap.h"
#include "Characters/TheGalleryCharacter.h"

// Sets default values
ADartTrap::ADartTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  sceneComp_ = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComp_);

  // Create Tripwire Mesh
  tripwireMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TripwireMesh"));
  tripwireMesh_->SetupAttachment(sceneComp_);

  // Create Tripwire Collision
  tripwireCollisionComp_ = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  tripwireCollisionComp_->InitBoxExtent(FVector(10, 10, 1));
  tripwireCollisionComp_->SetupAttachment(sceneComp_);
  tripwireCollisionComp_->OnComponentBeginOverlap.AddDynamic(this, &ADartTrap::OnBeginOverlap);

  // Create Dart Mesh
  dartMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DartMesh"));
  dartMesh_->SetupAttachment(sceneComp_);
  dartMesh_->SetEnableGravity(false);
  dartMesh_->SetSimulatePhysics(false);

  // Create Dart Collision
  dartCollisionComp_ = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
  dartCollisionComp_->InitSphereRadius(100);
  dartCollisionComp_->SetupAttachment(dartMesh_);
  dartCollisionComp_->OnComponentBeginOverlap.AddDynamic(this, &ADartTrap::OnDartHit);

  dartVelocity_ = FVector(300.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ADartTrap::BeginPlay()
{
	Super::BeginPlay();

  dartLocation_ = dartMesh_->RelativeLocation;
}

// Called every frame
void ADartTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADartTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

  if (Character)
  {
    // Activate the dart trap
    if (!activated_)
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

void ADartTrap::OnDartHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  if (activated_)
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

void ADartTrap::ShootDart()
{
  DebugLog("Shoot Dart from the dart trap");
  activated_ = true;
  dartMesh_->Activate();
  dartMesh_->SetSimulatePhysics(true);
  dartMesh_->SetRelativeLocationAndRotation(dartLocation_, FQuat());
  dartMesh_->AddImpulse(dartVelocity_);
  GetWorldTimerManager().SetTimer(resetTimerHandle_, this, &ADartTrap::ResetDart, timeToReset_, false);
}

void ADartTrap::ResetDart()
{
  DebugLog("Reset the dart trap");
  dartMesh_->SetRelativeLocationAndRotation(dartLocation_, FQuat());
  dartMesh_->SetSimulatePhysics(false);
  dartMesh_->Deactivate();
  activated_ = false;

  FString text = "X: ";
  text.AppendInt(dartLocation_.X);
  text.Append(", Y:");
  text.AppendInt(dartLocation_.Y);
  text.Append(", Z:");
  text.AppendInt(dartLocation_.Z);
  DebugLog(text);
}