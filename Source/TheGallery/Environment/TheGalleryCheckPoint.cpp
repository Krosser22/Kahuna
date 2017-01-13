// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryCheckPoint.h"
#include "Characters/Player/TheGalleryCharacter.h"
#include "Game/TheGalleryGameInstance.h"

// Sets default values
ATheGalleryCheckPoint::ATheGalleryCheckPoint(const class FObjectInitializer& PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Create Scene
  SceneComponent = PCIP.CreateDefaultSubobject<USceneComponent>(this, TEXT("Scene"));
  SetRootComponent(SceneComponent);

  // Create Tripwire Mesh
  MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
  MeshComponent->SetupAttachment(SceneComponent);

  // Create Tripwire Collision
  CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  CollisionComponent->InitBoxExtent(FVector(10, 10, 1));
  CollisionComponent->SetupAttachment(MeshComponent);
  CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryCheckPoint::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ATheGalleryCheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryCheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheGalleryCheckPoint::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);
  UTheGalleryGameInstance* GameInstance = Cast<UTheGalleryGameInstance>(GetGameInstance());
  if (Character && GameInstance)
  {
    GameInstance->SetCheckPoint(GetActorLocation());
		PlaySound();
  }
}

void ATheGalleryCheckPoint::PlaySound_Implementation()
{

}
