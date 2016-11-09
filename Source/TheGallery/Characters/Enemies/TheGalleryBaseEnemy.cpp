// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseEnemy.h"

// Sets default values
ATheGalleryBaseEnemy::ATheGalleryBaseEnemy()
{
  // Create Collision
  AttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBoxCollision"));
  AttackCollisionComponent->InitBoxExtent(FVector(10, 10, 10));
  AttackCollisionComponent->SetupAttachment(RootComponent);
}

void ATheGalleryBaseEnemy::CharacterDeath()
{
  DebugLog("Enemy killed");
  Destroy();
}

bool ATheGalleryBaseEnemy::isFreezed()
{
  return IsFreezed;
}

bool ATheGalleryBaseEnemy::isKnockedBack()
{
  return IsKnockedBack;
}

bool ATheGalleryBaseEnemy::isDead()
{
  return IsDead;
}

bool ATheGalleryBaseEnemy::isAttackOnCD()
{
  return IsAttackOnCD;
}

void ATheGalleryBaseEnemy::attack()
{
  TArray<AActor*> baseCharacter;
  AttackCollisionComponent->GetOverlappingActors(baseCharacter);

  for (auto actor : baseCharacter)
  {
    ATheGalleryBaseCharacter *character = Cast<ATheGalleryBaseCharacter>(actor);

    if (character)
    {
      if (character != this)
      {
        actor->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
      }
    }
  }

  IsAttackOnCD = true;
  GetWorldTimerManager().SetTimer(AttackCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDAttack, AttackCD, false);
}

bool ATheGalleryBaseEnemy::isSpitPoisonOnCD()
{
  if (IsSpitPoisonOnCD) DebugLog("YES");
  else DebugLog("NO");
  return IsSpitPoisonOnCD;
}

void ATheGalleryBaseEnemy::spitPoison()
{
  DebugLog("SpitPoison");
  IsSpitPoisonOnCD = true;
  GetWorldTimerManager().SetTimer(SpitPoisonCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDSpitPoison, SpitPoisonCD, false);
}

void ATheGalleryBaseEnemy::FinishCDAttack()
{
  IsAttackOnCD = false;
}

void ATheGalleryBaseEnemy::FinishCDSpitPoison()
{
  IsSpitPoisonOnCD = false;
}