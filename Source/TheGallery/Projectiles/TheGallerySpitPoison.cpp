// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGallerySpitPoison.h"
#include "Characters/Player/TheGalleryCharacter.h"

// Sets default values
ATheGallerySpitPoison::ATheGallerySpitPoison()
{

}

// Called when the game starts or when spawned
void ATheGallerySpitPoison::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ATheGallerySpitPoison::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ATheGallerySpitPoison::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryCharacter* actor = Cast<ATheGalleryCharacter>(OtherActor);
  if (actor)
  {
    actor->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
    Destroy();
  }
}