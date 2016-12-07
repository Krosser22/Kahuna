// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryRotatingLilyPad.h"

// Sets default values
ATheGalleryRotatingLilyPad::ATheGalleryRotatingLilyPad(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(SceneComponent);

  // Create TargetPoint
  Center = CreateDefaultSubobject<USphereComponent>(TEXT("Center"));
  Center->SetupAttachment(SceneComponent);
  Center->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ATheGalleryRotatingLilyPad::BeginPlay()
{
	Super::BeginPlay();

  FActorSpawnParameters SpawnParams;
  SpawnParams.Owner = this;
  SpawnParams.Instigator = Instigator;

  FQuat rotation = FQuat(Center->GetComponentRotation());
  rotation.Z += VelocityOfRotationOfLilyPads;
  Center->SetRelativeRotation(rotation);
  FVector loctaion = Center->GetComponentLocation();

  float xFinal, yFinal;
  int32 xInicial = loctaion.X + DistanceFromCenter * cos(2 * 3.14f / AmountOfLilyPads);
  int32 yInicial = loctaion.Y + DistanceFromCenter * sin(2 * 3.14f / AmountOfLilyPads);
  
  ATheGalleryLilyPadTrap *lilyPadTrap = nullptr;
  for (int32 i = 0; i < AmountOfLilyPads; ++i)
  {
    lilyPadTrap = GetWorld()->SpawnActor<ATheGalleryLilyPadTrap>(LilyPadTrapTemplate, loctaion, Center->GetComponentRotation(), SpawnParams);

    if (lilyPadTrap)
    {
      lilyPadTrap->AttachToActor(Center->GetAttachmentRootActor(), FAttachmentTransformRules::SnapToTargetIncludingScale);
      xFinal = loctaion.X + DistanceFromCenter * cos(2 * 3.14f / AmountOfLilyPads * i);
      yFinal = loctaion.Y + DistanceFromCenter * sin(2 * 3.14f / AmountOfLilyPads * i);

      lilyPadTrap->SetActorRotation(rotation);
      lilyPadTrap->SetActorLocation(FVector(xFinal, yFinal, loctaion.Z));

      xInicial = xFinal;
      yInicial = yFinal;

      LilyPadsList.Push(lilyPadTrap);
    }
  }
}

// Called every frame
void ATheGalleryRotatingLilyPad::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  this->AddActorWorldRotation(FQuat(FVector(0.0f, 0.0f, 1.0f), VelocityOfRotationOfLilyPads * DeltaTime));
}