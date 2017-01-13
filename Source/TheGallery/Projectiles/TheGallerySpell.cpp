// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGallerySpell.h"

// Sets default values
ATheGallerySpell::ATheGallerySpell()
{

}

// Called when the game starts or when spawned
void ATheGallerySpell::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ATheGallerySpell::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ATheGallerySpell::SetInitialValues(FSpellInfo SpellInfo)
{
  Data = SpellInfo;
  Lifetime = Data.ProjectileLifeTime;
}

void ATheGallerySpell::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  ATheGalleryBaseCharacter* DamagedCharacter = Cast<ATheGalleryBaseCharacter>(OtherActor);
  if (DamagedCharacter && Owner && DamagedCharacter != Owner)
  {
    switch (Data.Effect)
    {
      case ESpellEffect::SE_Freeze:
        Freeze(DamagedCharacter);
      break;

      case ESpellEffect::SE_AoEDamage:
        RadialDamage(DamagedCharacter);
      break;

      case ESpellEffect::SE_None:
        ApplyDamage(DamagedCharacter);
      break;
    }
    Destroy();
  }
}

void ATheGallerySpell::Freeze(ATheGalleryBaseCharacter* Target)
{
  Target->FreezeCharacter(Data.EffectValue);
  ApplyDamage(Target);
}

void ATheGallerySpell::RadialDamage(ATheGalleryBaseCharacter* Target)
{
  for (TActorIterator<ATheGalleryBaseCharacter> Character(GetWorld()); Character; ++Character)
  {
    if ((*Character) != Owner)
    {
      float distance = GetDistanceTo(*Character);
      if (distance <= Data.EffectValue)
      {
        ApplyDamage(*Character);
      }
    }
  }
}

void ATheGallerySpell::ApplyDamage(ATheGalleryBaseCharacter* Target)
{
  //To-Do: Knock Back
  Target->TakeDamage(Data.Damage, FDamageEvent(), Owner->GetController(), Owner);
}
