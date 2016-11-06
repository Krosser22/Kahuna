// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryLilyPadTrap.h"
#include "Characters/TheGalleryBaseCharacter.h"

// Sets default values
ATheGalleryLilyPadTrap::ATheGalleryLilyPadTrap(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(SceneComponent);

  // Create Collision
  CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  CollisionComponent->InitBoxExtent(FVector(10, 10, 1));
  CollisionComponent->SetupAttachment(SceneComponent);
  CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryLilyPadTrap::OnBeginOverlap);

  // Create Mesh
  MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  MeshComponent->SetupAttachment(CollisionComponent);

  // Create Scene
  SceneComponentToSink = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("DistanceToSink"));
  SceneComponentToSink->SetupAttachment(SceneComponent);
  SceneComponentToSink->SetRelativeLocation(FVector(0.0f, 0.0f, -22.22f));
}

// Called when the game starts or when spawned
void ATheGalleryLilyPadTrap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryLilyPadTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
  if (State == ELilyPadState::ELilyPadStateSinking)
  {
    CollisionComponent->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, SceneComponentToSink->RelativeLocation, Alpha));
    Alpha += SpeedOfSink;
  }
  else if (State == ELilyPadState::ELilyPadStateSinkingOff)
  {
    CollisionComponent->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, SceneComponentToSink->RelativeLocation, Alpha));
    Alpha -= SpeedOfSink;
  }
}

void ATheGalleryLilyPadTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryBaseCharacter* baseCharacter = Cast<ATheGalleryBaseCharacter>(OtherActor);
 
  if (baseCharacter && State == ELilyPadState::ELilyPadStateWaiting)
  {
    // A Character has hit the Lily Pad Trap
    State = ELilyPadState::ELilyPadStatePreparingToSink;
    GetWorldTimerManager().SetTimer(SinkTimerHandle, this, &ATheGalleryLilyPadTrap::Sink, TimeUntilSinking, false);
  }
}

void ATheGalleryLilyPadTrap::Sink()
{
  // TheGalleryLilyPadTrap sinking
  Alpha = 0.0f;
  State = ELilyPadState::ELilyPadStateSinking;
  GetWorldTimerManager().SetTimer(SinkTimerHandle, this, &ATheGalleryLilyPadTrap::WaitingToSinkOff, TimeUntilSinking, false);
  // TODO: Start the sink animation
}

void ATheGalleryLilyPadTrap::WaitingToSinkOff()
{
  // TheGalleryLilyPadTrap waiting To Sink off
  State = ELilyPadState::ELilyPadStateWaitingToSinkOff;
  GetWorldTimerManager().SetTimer(SinkTimerHandle, this, &ATheGalleryLilyPadTrap::SinkOff, TimeToBeSinked, false);
}

void ATheGalleryLilyPadTrap::SinkOff()
{
  // TheGalleryLilyPadTrap sinking off
  State = ELilyPadState::ELilyPadStateSinkingOff;
  GetWorldTimerManager().SetTimer(SinkTimerHandle, this, &ATheGalleryLilyPadTrap::FinishOfSinkOff, TimeToBeSinked, false);
  // TODO: Start the sink off animation

  TArray<AActor*> baseCharacter;
  CollisionComponent->GetOverlappingActors(baseCharacter);
  for (auto actor : baseCharacter)
  {
    ATheGalleryBaseCharacter *character = Cast<ATheGalleryBaseCharacter>(actor);

    if (character)
    {
      actor->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
    }
  }
}

void ATheGalleryLilyPadTrap::FinishOfSinkOff()
{
  // TheGalleryLilyPadTrap ready again
  State = ELilyPadState::ELilyPadStateWaiting;
  CollisionComponent->SetRelativeLocation(FVector::ZeroVector);
}