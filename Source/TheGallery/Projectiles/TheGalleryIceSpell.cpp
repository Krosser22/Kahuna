// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryIceSpell.h"

// Sets default values
ATheGalleryIceSpell::ATheGalleryIceSpell()
{

}

// Called when the game starts or when spawned
void ATheGalleryIceSpell::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ATheGalleryIceSpell::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ATheGalleryIceSpell::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}