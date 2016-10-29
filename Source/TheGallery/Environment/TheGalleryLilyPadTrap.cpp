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
  sceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(sceneComponent);

  // Create Collision
  collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  collisionComponent->InitBoxExtent(FVector(10, 10, 1));
  collisionComponent->SetupAttachment(sceneComponent);
  collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryLilyPadTrap::OnBeginOverlap);

  // Create Mesh
  meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  meshComponent->SetupAttachment(collisionComponent);
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
  
  if (state == ELilyPadState::ELilyPadStateSinking)
  {
    collisionComponent->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, FVector(0.0f, 0.0f, distanceToSink), alpha));
    alpha += speedOfSink;
  }
  else if (state == ELilyPadState::ELilyPadStateSinkingOff)
  {
    collisionComponent->SetRelativeLocation(FMath::Lerp(FVector::ZeroVector, FVector(0.0f, 0.0f, distanceToSink), alpha));
    alpha -= speedOfSink;
  }
}

void ATheGalleryLilyPadTrap::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryBaseCharacter* baseCharacter = Cast<ATheGalleryBaseCharacter>(OtherActor);
 
  if (baseCharacter && state == ELilyPadState::ELilyPadStateWaiting)
  {
    //DebugLog("A Character has hit the Lily Pad Trap");
    state = ELilyPadState::ELilyPadStatePreparingToSink;
    GetWorldTimerManager().SetTimer(sinkTimerHandle, this, &ATheGalleryLilyPadTrap::Sink, timeUntilSinking, false);
  }
}

void ATheGalleryLilyPadTrap::Sink()
{
  //DebugLog("TheGalleryLilyPadTrap sinking");
  alpha = 0.0f;
  state = ELilyPadState::ELilyPadStateSinking;
  GetWorldTimerManager().SetTimer(sinkTimerHandle, this, &ATheGalleryLilyPadTrap::WaitingToSinkOff, timeUntilSinking, false);
  // TODO: Start the sink animation
}

void ATheGalleryLilyPadTrap::WaitingToSinkOff()
{
  //DebugLog("TheGalleryLilyPadTrap waiting To Sink off");
  state = ELilyPadState::ELilyPadStateWaitingToSinkOff;
  GetWorldTimerManager().SetTimer(sinkTimerHandle, this, &ATheGalleryLilyPadTrap::SinkOff, timeToBeSinked, false);
}

void ATheGalleryLilyPadTrap::SinkOff()
{
  //DebugLog("TheGalleryLilyPadTrap sinking off");
  state = ELilyPadState::ELilyPadStateSinkingOff;
  GetWorldTimerManager().SetTimer(sinkTimerHandle, this, &ATheGalleryLilyPadTrap::FinishOfSinkOff, timeToBeSinked, false);
  // TODO: Start the sink off animation

  TArray<AActor*> baseCharacter;
  collisionComponent->GetOverlappingActors(baseCharacter);
  for (auto actor : baseCharacter)
  {
    ATheGalleryBaseCharacter *character = Cast<ATheGalleryBaseCharacter>(actor);

    if (character)
    {
      actor->TakeDamage(damage, FDamageEvent(), nullptr, nullptr);
    }
  }
}

void ATheGalleryLilyPadTrap::FinishOfSinkOff()
{
  //DebugLog("TheGalleryLilyPadTrap ready again");
  state = ELilyPadState::ELilyPadStateWaiting;
  collisionComponent->SetRelativeLocation(FVector::ZeroVector);
}