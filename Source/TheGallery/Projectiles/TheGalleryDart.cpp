// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryDart.h"
#include "Characters/Player/TheGalleryCharacter.h"

// Sets default values
ATheGalleryDart::ATheGalleryDart()
{

}

// Called when the game starts or when spawned
void ATheGalleryDart::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryDart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheGalleryDart::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryBaseCharacter* actor = Cast<ATheGalleryBaseCharacter>(OtherActor);

  if (actor)
  {
    actor->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
    Destroy();
  }
}